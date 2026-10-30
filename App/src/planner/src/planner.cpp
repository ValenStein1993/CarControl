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
#include "common/map_utils.hpp"
#include "common/config_app.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

int angleBin(float theta) {
  // wrap angle to [0, 2pi]
  float t = std::remainder(theta, 2.0f * std::numbers::pi_v<float>);
  if (t < 0) t += 2.0f * std::numbers::pi_v<float>;
  return static_cast<int>(t / (2.0f * std::numbers::pi_v<float>) * n_binsAngle) % n_binsAngle;
}


Planner::Planner()
  : BaseNode("planner"), 
    closestNode_{0.0f, 0.0f, 0.0f, -1, -1},
    mapReady_{false} {

  declare_parameter<float>("x_target", 0.0f);
	declare_parameter<float>("y_target", 0.0f);

  get_parameter("x_target", target_.first);
  get_parameter("y_target", target_.second);

  add_timer(10ms, &Planner::publish_motionControl);

  if (debug_) {
    add_timer(100ms, &Planner::publish_debugMsg);
  }

  pub_debugPlanner_ = create_publisher<car_msgs::msg::DebugPlanner>(
    static_cast<std::string>(config_topics_debugPlanner), 10);
  pub_motionControl_ = create_publisher<car_msgs::msg::MotionControl>(
    static_cast<std::string>(config_topics_motionControl), 10);
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
    std::bind(&Planner::callback_laserscan, this, _1));
}

void Planner::callback_vehiclePose(const geometry_msgs::msg::PoseStamped::SharedPtr msg) {
  lastVehiclePose_ = msg;
}

void Planner::callback_occGrid(const nav_msgs::msg::OccupancyGrid::SharedPtr msg) {
  lastOccGrid_ = msg;
  nav_msgs::msg::MapMetaData* newGridMeta = &(msg->info);
  // convert existing path to the new grid structure
  path_ = transformPathToNewGrid(newGridMeta);
  gridMetaData_ = newGridMeta;

  if (!mapReady_) mapReady_ = checkMapReady();

  // calculate path only if map is ready
  if (mapReady_) {
    setTargetPoint();
    publish_path();
  }
}

void Planner::callback_laserscan(const sensor_msgs::msg::LaserScan::SharedPtr msg) {
  lastLaserScan_ = msg;
  distAhead_ = msg->ranges[0.5 * msg->ranges.size()];
}

void Planner::publish_motionControl() 
{

  if (!lastVehiclePose_) {
    RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000, "Cannot plan motion: Vehicle pose is unavailable.");
    return;
  }

  if (path_.empty()) {
    RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000, "Cannot plan motion: Vehicle path is unavailable.");
    return;
  }

  if (!lastOccGrid_) {
    RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000, "Cannot plan motion: Map is unavailable.");
    return;
  }

  auto [speed, steering_angle] = calcSteering();
  float yaw_rate = (speed / config_vehicle_wheelbase) * std::tan(steering_angle);

  car_msgs::msg::MotionControl msg;
  msg.yaw_rate = yaw_rate; 
  msg.speed = speed; 

  pub_motionControl_->publish(msg);
}

void Planner::publish_debugMsg()
{
  debugPlannerMsg_.header.stamp = get_clock()->now();
  pub_debugPlanner_->publish(debugPlannerMsg_);
}


void Planner::publish_path() 
{
  if (!lastVehiclePose_) {
    RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000, "Cannot find path: Vehicle pose is unavailable.");
    return;
  }

  if (!lastOccGrid_) {
    RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000, "Cannot find path: Map is unavailable.");
    return;
  }

  setClosestNode();

  if (closestNode_.idx == -1) {

    path_ = findShortestPath(lastVehiclePose_->pose.position.x, lastVehiclePose_->pose.position.y,
       tf2::getYaw(lastVehiclePose_->pose.orientation), idx_target_);
  }
  else {
    std::vector<int> path_update = findShortestPath(closestNode_.x, closestNode_.y, closestNode_.theta, idx_target_);

    path_update.insert(path_update.begin(), path_.begin(), path_.begin() + closestNode_.idx + 1);
    path_ = path_update;
  }

  nav_msgs::msg::Path pathMsg;
  pathMsg.header.stamp = get_clock()->now();
  pathMsg.header.frame_id = config_frames_odom;

  for (int idx : path_) {
    auto [x, y] = Common::MapUtils::getPosFromMapIndex(idx, gridMetaData_);

    geometry_msgs::msg::PoseStamped pose;
    pose.pose.position.x = x;
    pose.pose.position.y = y;
    pathMsg.poses.push_back(pose);
  }
  pub_path_->publish(pathMsg);
}

std::vector<int> Planner::transformPathToNewGrid(const nav_msgs::msg::MapMetaData* newMeta) {
  std::vector<int> transformed;

  transformed.reserve(path_.size());

  for (int idx : path_) {
    // Convert old-grid cell position into world coordinates, then project into new grid
    const auto [x_world, y_world] = Common::MapUtils::getPosFromMapIndex(idx, gridMetaData_);
    const int newIdx = Common::MapUtils::getMapIndexFromPos(x_world, y_world, newMeta);

    if (newIdx != -1) {
      transformed.push_back(newIdx);
    }
  }

  return transformed;
}

void Planner::setTargetPoint() {
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

  idx_target_ = idx;
}

void Planner::setClosestNode() {
  float pos_x = lastVehiclePose_->pose.position.x;
  float pos_y = lastVehiclePose_->pose.position.y;
  
  float dist_closestNode = std::numeric_limits<float>::max();
  int init_search;
  if (closestNode_.idx == -1) {
    init_search = 0;
  }
  else {
    init_search = closestNode_.idx;
  }

  for (size_t i = init_search; i < path_.size(); ++i) {
    auto [x, y] = Common::MapUtils::getPosFromMapIndex(path_[i], gridMetaData_);
    float distance = std::hypot(x - pos_x, y - pos_y);
    if (distance < dist_closestNode) {
      dist_closestNode = distance;
      closestNode_ = {x, y, 0.0f, -1, static_cast<int>(i)};
    }
  }

  float x_closestNodePrev = closestNode_.x;
  float y_closestNodePrev = closestNode_.y;
  float x_closestNodeNext = closestNode_.x;
  float y_closestNodeNext = closestNode_.y;

  if (closestNode_.idx > 0) {
    std::tie(x_closestNodePrev, y_closestNodePrev) = Common::MapUtils::getPosFromMapIndex(path_[closestNode_.idx - 1], gridMetaData_);
  }

  if (static_cast<size_t>(closestNode_.idx) < (path_.size() - 1)) {
    std::tie(x_closestNodeNext, y_closestNodeNext) = Common::MapUtils::getPosFromMapIndex(path_[closestNode_.idx + 1], gridMetaData_);
  }

  closestNode_.theta = std::atan2(y_closestNodeNext - y_closestNodePrev, x_closestNodeNext - x_closestNodePrev);
}

std::pair<float, float> Planner::calcSteering() {
  float pos_x = lastVehiclePose_->pose.position.x;
  float pos_y = lastVehiclePose_->pose.position.y;
  float phi = tf2::getYaw(lastVehiclePose_->pose.orientation);
  
  setClosestNode();

  // stanley controller
  float cte = (pos_y - closestNode_.y) * std::cos(closestNode_.theta) - (pos_x - closestNode_.x) * std::sin(closestNode_.theta);
  float speed = std::lerp(0, maxSpeed, std::clamp(
    (distAhead_ - minDist) / (maxSpeedDist - minDist), 0.0f, 1.0f));  
  float heading_error = closestNode_.theta - phi;
  float steering_angle = std::clamp(
    static_cast<float>(heading_error + std::atan2(gain_cte * -cte ,(speed + 0.001))),
    -config_vehicle_max_steering, 
    config_vehicle_max_steering);

  float yaw_rate = (speed / config_vehicle_wheelbase) * std::tan(steering_angle);

  if (debug_) {
    debugPlannerMsg_.yaw_rate = yaw_rate;
    debugPlannerMsg_.speed = speed;
    debugPlannerMsg_.steering_angle = steering_angle;
    debugPlannerMsg_.pdx_cnode = closestNode_.idx;
    debugPlannerMsg_.cte = std::atan(gain_cte * cte / speed);
    debugPlannerMsg_.heading_error = heading_error;
  }
  return {speed, steering_angle};
}

std::vector<int> Planner::findShortestPath(float x_start, float y_start, float theta_start, int idx_target) {
  // hybrid-A* Algorithm  

  float x_tar, y_tar;
  std::tie(x_tar, y_tar) = Common::MapUtils::getPosFromMapIndex(idx_target, gridMetaData_);
  int idx_found = -1;

  float stepsize = 1.5 * gridMetaData_->resolution;
  std::vector<int8_t> occgrid = lastOccGrid_->data;

  // pq = {{distance, vertex}, ...}
  std::priority_queue<
    std::pair<float, int>, 
    std::vector<std::pair<float, int>>, 
    std::greater<std::pair<float, int>>> pq;

  std::map<int, GridNode> nodes; 

  // add start vertex to queue and dict
  int idx_start = Common::MapUtils::getMapIndexFromPos(x_start, y_start, gridMetaData_) * n_binsAngle + angleBin(theta_start);
  pq.emplace(0, idx_start);

  GridNode n{x_start, y_start, theta_start, 0.0f, -1};
  nodes[idx_start] = n; 

  while (!pq.empty()) {
    // select closest vertex u from the queue
    auto top = pq.top();
    pq.pop();

    float d_u = top.first;  
    int idx_u = top.second; 
    GridNode n_u = nodes[idx_u];

    // continue when checked vertex is stale
    if (d_u > n_u.dist)
        continue;

    // stop when target node is found
    //if (idx_u == idx_target)
    //  break;
    float dx = n_u.x - x_tar;
    float dy = n_u.y - y_tar;
    if (std::hypot(dx, dy) < 3*stepsize) {  
        idx_found = idx_u;
        break;
    }

    // forward expansion to neighbors
    float v_x, v_y, v_theta;
    for (int dir : {-1, 1}) {
      for (float theta : {-config_vehicle_max_steering, 0.0f, config_vehicle_max_steering}) {
        float s = dir * stepsize;
        if (theta == 0.0f) {
          v_x = n_u.x + s * std::cos(n_u.theta);
          v_y = n_u.y + s * std::sin(n_u.theta);
          v_theta = n_u.theta;
        }
        else {
          float rad_turn = config_vehicle_wheelbase / std::tan(theta);                  
          float dTheta = s / rad_turn;
          v_x = n_u.x + rad_turn * (std::sin(n_u.theta + dTheta) - std::sin(n_u.theta));
          v_y = n_u.y - rad_turn * (std::cos(n_u.theta + dTheta) - std::cos(n_u.theta));
          v_theta = n_u.theta + dTheta;
        }

        if (!Common::MapUtils::checkGridBoundries(v_x, v_y, gridMetaData_)) continue;

        // 2d index
        int idx_v = Common::MapUtils::getMapIndexFromPos(v_x, v_y, gridMetaData_);
        // 3d index
        int idx_t = angleBin(v_theta);
        int idx_vt = idx_v * n_binsAngle + idx_t;

        int8_t c = occgrid[idx_v];

        if (c >= cost_inscribed) continue;
        float risk_weight = 1.0f; 
        float step = stepsize * (1.0f + risk_weight * c / 100.0f);
        if (dir == -1) step *= 2.0f;          // reverse penalty
        if (theta != 0.0f) step *= 1.1f;      // small turning penalty

        float d_v = n_u.dist + step;

        // if distance to v through u is shorter, update distance and parent
        if (!nodes.contains(idx_vt) || d_v < nodes[idx_vt].dist) {
          GridNode n{v_x, v_y, v_theta, d_v, idx_u};
          nodes[idx_vt] = n; 
          pq.emplace(d_v, idx_vt);
        }
      }
    }
  }

  // construct path
  std::vector<int> path;
  if (idx_found == -1) {
    return path;
  }
  int idx_c = idx_found;

  while (idx_c != -1) {
    path.push_back(idx_c / n_binsAngle);
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

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Planner>());
  rclcpp::shutdown();
  return 0;
}