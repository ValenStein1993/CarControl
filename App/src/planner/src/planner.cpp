#include <memory>
#include <cmath>
#include <chrono>
#include <queue>
#include <vector>
#include <climits>
#include <utility>
#include <numbers>
#include <algorithm>
#include <tf2/utils.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <map>

#include "planner/planner.hpp"
#include "rclcpp/rclcpp.hpp"
#include "car_msgs/msg/vehicle_state.hpp"
#include "car_msgs/msg/motion_control.hpp"
#include <sensor_msgs/msg/laser_scan.hpp>
#include "common/config.hpp"
#include "common/utils.hpp"
#include "common/config_app.hpp"
#include "common/datatypes.hpp"


using namespace std::chrono_literals;
using std::placeholders::_1;

int angleBin(float theta) {
  // wrap angle to [0, 2pi]
  float t = Common::MathUtils::wrapAngle(theta);
  if (t < 0) t += 2.0f * std::numbers::pi_v<float>;
  return static_cast<int>(t / (2.0f * std::numbers::pi_v<float>) * n_binsAngle) % n_binsAngle;
}

Pose motion(const Pose& p, float s, float phi) {
  // bicycle model for front axle
  if (phi == 0.0f) {
    return {p.x + s * std::cos(p.th), p.y + s * std::sin(p.th), p.th};
  }
  const float R = config_vehicle_wheelbase / std::sin(phi);
  const float dth = s / R;
  const float a = p.th + phi;
  return {p.x + R * (std::sin(a + dth) - std::sin(a)),
          p.y - R * (std::cos(a + dth) - std::cos(a)),
          p.th + dth};
}


Planner::Planner()
  : BaseNode("planner"), 
    updateNode_{0.0f, 0.0f, 0.0f, 0.0f, -1},
    mapReady_{false} {

  declare_parameter<float>("x_target", 0.0f);
	declare_parameter<float>("y_target", 0.0f);

  get_parameter("x_target", target_.first);
  get_parameter("y_target", target_.second);

  add_timer(1000ms, &Planner::publish_path);

  pub_path_ = create_publisher<nav_msgs::msg::Path>(
    static_cast<std::string>(config_topics_globalPath), 10);

  sub_vehiclePose_ = create_subscription<geometry_msgs::msg::PoseStamped>(
    static_cast<std::string>(config_topics_poseCrtgrphr), 10, 
    std::bind(&Planner::callback_vehiclePose, this, _1));
  sub_occGrid_ = create_subscription<nav_msgs::msg::OccupancyGrid>(
    static_cast<std::string>(config_topics_costMap), 10, 
    std::bind(&Planner::callback_occGrid, this, _1));
  sub_laserScan_ = create_subscription<sensor_msgs::msg::LaserScan>(
    static_cast<std::string>(config_topics_laserScan), 10, 
    std::bind(&Planner::callback_laserScan, this, _1));
  sub_closestNode_ = create_subscription<car_msgs::msg::PathNode>(
    static_cast<std::string>(config_topics_closestNode), 10, 
    std::bind(&Planner::callback_closestNode, this, _1));

  tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
}

void Planner::callback_vehiclePose(const geometry_msgs::msg::PoseStamped::SharedPtr msg) {
  std::string vehicle_base_frame = "base_link";
  std::string front_axle_frame = "front_axle_link";

  if (!tf_buffer_->canTransform(vehicle_base_frame, front_axle_frame, tf2::TimePointZero)) {
    return;
  }

  const auto base_to_front_axle = tf_buffer_->lookupTransform(
      vehicle_base_frame, front_axle_frame, tf2::TimePointZero);

  tf2::Transform map_to_chassis;
  tf2::fromMsg(msg->pose, map_to_chassis);

  tf2::Transform chassis_to_front_axle_tf;
  tf2::fromMsg(base_to_front_axle.transform, chassis_to_front_axle_tf);

  const tf2::Transform map_to_front_axle = map_to_chassis * chassis_to_front_axle_tf;

  geometry_msgs::msg::PoseStamped front_axle_pose;
  front_axle_pose.header = msg->header;
  front_axle_pose.pose.position.x = map_to_front_axle.getOrigin().x();
  front_axle_pose.pose.position.y = map_to_front_axle.getOrigin().y();
  front_axle_pose.pose.position.z = map_to_front_axle.getOrigin().z();
  front_axle_pose.pose.orientation = tf2::toMsg(map_to_front_axle.getRotation());
  lastVehiclePose_ = std::make_shared<geometry_msgs::msg::PoseStamped>(front_axle_pose);
}

void Planner::callback_laserScan(const sensor_msgs::msg::LaserScan::SharedPtr msg) {
  lastLaserScan_ = msg;
}

void Planner::callback_occGrid(const nav_msgs::msg::OccupancyGrid::SharedPtr msg) {
  lastOccGrid_ = msg;
  gridMetaData_ = &(msg->info);

  if (!mapReady_) mapReady_ = checkMapReady();
  if (mapReady_) setTargetNode();
  if (path_.empty()) publish_path();
  
}

void Planner::callback_closestNode(const car_msgs::msg::PathNode::SharedPtr msg) {

  if (!path_.empty()) {
    const Pose& p_u = path_[msg->idx + 1];
    updateNode_ = {p_u.x, p_u.y, p_u.th, 0.0f, msg->idx + 1};
  }
}

void Planner::publish_path() {
  if (!lastVehiclePose_) {
    RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000, "Cannot find path: Vehicle pose is unavailable.");
    return;
  }

  if (!mapReady_) {
    RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000, "Cannot find path: Map is not ready.");
    return;
  }

  if (updateNode_.idx == -1) {
    GridNode startNode{static_cast<float>(lastVehiclePose_->pose.position.x), 
      static_cast<float>(lastVehiclePose_->pose.position.y),
      static_cast<float>(tf2::getYaw(lastVehiclePose_->pose.orientation)), 0.0f, -1};

    path_ = findShortestPath(startNode);
  }
  else {
    std::vector<Pose> path_update = findShortestPath(updateNode_);

    if (!path_update.empty()) {
      path_update.insert(path_update.begin(), path_.begin(), path_.begin() + updateNode_.idx);
      path_ = path_update;
    }
  }

  nav_msgs::msg::Path pathMsg;
  pathMsg.header.stamp = get_clock()->now();
  pathMsg.header.frame_id = config_frames_odom;

  for (const auto& p : path_) {
    geometry_msgs::msg::PoseStamped pose;
    pose.header = pathMsg.header;
    pose.pose.position.x = p.x;
    pose.pose.position.y = p.y;
    tf2::Quaternion q;
    q.setRPY(0.0, 0.0, p.th);
    pose.pose.orientation = tf2::toMsg(q);
    pathMsg.poses.push_back(pose);
  }
  pub_path_->publish(pathMsg);
}

void Planner::setTargetNode() {
  if (!lastVehiclePose_) {
      RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000, "Cannot adjust target: Vehicle pose is unavailable.");
      return;
  }

  const auto& vehiclePos = lastVehiclePose_->pose.position;

  float xTarget = target_.first;
  float yTarget = target_.second;

  float dx = xTarget - vehiclePos.x;
  float dy = yTarget - vehiclePos.y;

  float distance = std::hypot(dx, dy);

  float dirX = dx / distance;
  float dirY = dy / distance;

  int idx = Common::MapUtils::getMapIndexFromPos(xTarget, yTarget, gridMetaData_);

  const float step = gridMetaData_->resolution;
  const int maxIterations = static_cast<int>(distance / step) + 1;

  for (int i = 0; idx == -1 && i < maxIterations; ++i) {
      xTarget -= dirX * step;
      yTarget -= dirY * step;

      idx = Common::MapUtils::getMapIndexFromPos(xTarget, yTarget, gridMetaData_);
  }

  if (idx == -1) {
      RCLCPP_WARN(this->get_logger(),"Could not find a valid target position inside the map.");
      return;
  }

  targetNode_ = {xTarget, yTarget, 0.0f};
}


std::vector<Pose> Planner::findShortestPath(GridNode startNode) {
  // hybrid-A* Algorithm  
  startNode.idx = -1;
  int idx_found = -1;

  const float x0 = gridMetaData_->origin.position.x;
  const float y0 = gridMetaData_->origin.position.y;
  const int latticeW = static_cast<int>(std::ceil(gridMetaData_->width * gridMetaData_->resolution / latticeRes));
  const int latticeH = static_cast<int>(std::ceil(gridMetaData_->height * gridMetaData_->resolution / latticeRes));

  // reduce map resolution to lattice resolution
  auto stateIdx = [&](float x, float y, float theta) -> int {
    const int gx = static_cast<int>(std::floor((x - x0) / latticeRes));
    const int gy = static_cast<int>(std::floor((y - y0) / latticeRes));
    if (gx < 0 || gy < 0 || gx >= latticeW || gy >= latticeH) return -1;
    return (gy * latticeW + gx) * n_binsAngle + angleBin(theta);
  };

  const float stepsize = 1.5f * latticeRes;

  // pq = {{heuristic, distance, idx vertex}, ...}
  std::priority_queue<
    std::tuple<float, float, int>, 
    std::vector<std::tuple<float, float, int>>, 
    std::greater<std::tuple<float, float, int>>> pq;

  std::unordered_map<int, GridNode> nodes;

  // add start vertex to queue and dict
  int idx_start = stateIdx(startNode.x, startNode.y, startNode.theta);
  if (idx_start == -1) {
    RCLCPP_WARN(get_logger(), "Cannot find path: start pose is outside the map.");
    return {};
  }
  startNode.dist = 0.0f;
  pq.emplace(0.0, 0.0, idx_start);

  nodes[idx_start] = startNode; 

  while (!pq.empty()) {
    // select closest vertex u from the queue
    auto [h_u, d_u, idx_u] = pq.top();
    pq.pop();

    const GridNode n_u = nodes.at(idx_u);
    Pose p_u{n_u.x, n_u.y, n_u.theta};

    // continue when checked vertex is stale
    if (d_u > n_u.dist) continue;

    // stop when target node is found
    //if (idx_u == idx_target)
    //  break;
    float dx = n_u.x - targetNode_.x;
    float dy = n_u.y - targetNode_.y;
    if (std::hypot(dx, dy) < 3*stepsize) {  
        idx_found = idx_u;
        break;
    }

    // forward expansion to neighbors
    float max_planSteering = 0.9 * config_vehicle_max_steering;
    for (int dir : {-1, 1}) {
      for (float phi : {-max_planSteering, 0.0f, max_planSteering}) {
        float s = dir * stepsize;
        
        float avgCost;
        Pose p_v;
        float s_moved = moveVehicle(p_u, s, phi, p_v, avgCost);

        // check if vehicle moved at all (collision or out of map)
        if (s_moved == 0.0f) continue; 

        // 3d lattice index (x, y, theta)
        int idx_vt = stateIdx(p_v.x, p_v.y, p_v.th);
        if (idx_vt == -1 || idx_vt == idx_u) continue;

        float risk_weight = 1.0f; 
        float step = s_moved * (1.0f + risk_weight * avgCost / 100.0f);
        if (dir == -1) step *= 2.0f;          // reverse penalty
        if (phi != 0.0f) step *= 1.1f;      // small turning penalty

        float d_v = n_u.dist + step;

        auto it = nodes.find(idx_vt);
        if (it == nodes.end() || d_v < it->second.dist) {
          nodes.insert_or_assign(idx_vt, GridNode{p_v.x, p_v.y, p_v.th, d_v, idx_u});

          float h = std::hypot(p_v.x - targetNode_.x, p_v.y - targetNode_.y);
          pq.emplace(d_v + h, d_v, idx_vt);
        }
      }
    }
  }

  // construct path
  std::vector<Pose> path;
  if (idx_found == -1) {
    return path;
  }

  int idx_c = idx_found;

  while (idx_c != startNode.idx) {
    const GridNode& n = nodes.at(idx_c);
    path.push_back({n.x, n.y, Common::MathUtils::wrapAngle(n.theta)});
    idx_c = nodes.at(idx_c).idx;
  }
  std::reverse(path.begin(), path.end());
  return path;
}

bool Planner::checkMapReady() {
  if (!lastLaserScan_) return false;

  bool scanHasObs = false, mapHasObs = false;
  for (float r : lastLaserScan_->ranges) {
    if (std::isfinite(r) && r >= lastLaserScan_->range_min && r < lastLaserScan_->range_max) {
      scanHasObs = true;
      break;
    }
  }

  for (int c : lastOccGrid_->data) {
    if (c >= cost_inscribed) {
      mapHasObs = true;
      break;
    }
  }

  return !(scanHasObs ^ mapHasObs);
}

float Planner::moveVehicle(Pose& start, float s, float phi, Pose& end, float& avgCost) {
  Pose p;
  float x_check, y_check;

  float sum = 0.0f;
  const int n = std::max(1, static_cast<int>(std::ceil(std::abs(s) / (0.5f * gridMetaData_->resolution))));

  int i = 0;
  while (i < n) {
    p = motion(start, s * (i + 1) / n, phi);

    if (s < 0.0f) {
      x_check = p.x - config_vehicle_wheelbase * std::cos(p.th);
      y_check = p.y - config_vehicle_wheelbase * std::sin(p.th);
    } 
    else {
      x_check = p.x;
      y_check = p.y;
    } 

    // check if reference point is inside the map
    if (!Common::MapUtils::checkGridBoundries(x_check, y_check, gridMetaData_)) break;

    const int idx_c = Common::MapUtils::getMapIndexFromPos(x_check, y_check, gridMetaData_);
    int c = lastOccGrid_->data[idx_c];

    // check if reference point is in collision with obstacles
    if (c >= cost_inscribed) break;  

    // unknown: treat as moderately costly
    if (c < 0) c = 50; 

    sum += c;
    i++;
    end = p;
  }

  avgCost = sum / std::max(1, i);
  return std::abs(s * i / n);
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Planner>());
  rclcpp::shutdown();
  return 0;
}