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

#include "planner/planner.hpp"
#include "rclcpp/rclcpp.hpp"
#include "car_msgs/msg/vehicle_state.hpp"
#include "car_msgs/msg/motion_control.hpp"
#include <sensor_msgs/msg/laser_scan.hpp>
#include "common/config.hpp"
#include "common/map_utils.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

Planner::Planner()
  : BaseNode("planner"), 
    pIdx_closestNode_{-1} {

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
    static_cast<std::string>(config_topics_occupancyGrid), 10, 
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

  setTargetPoint();
  publish_path();

}

void Planner::callback_laserscan(const sensor_msgs::msg::LaserScan::SharedPtr msg) {
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

  if (debug_) {
    debugPlannerMsg_.yaw_rate = yaw_rate;
    debugPlannerMsg_.speed = speed;
    debugPlannerMsg_.steering_angle = steering_angle;
    debugPlannerMsg_.pdx_cnode = pIdx_closestNode_;
  }
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

  int idx_start;
  if (pIdx_closestNode_ == -1) {
    idx_start = Common::MapUtils::getMapIndexFromPos(
      lastVehiclePose_->pose.position.x, 
      lastVehiclePose_->pose.position.y, 
      gridMetaData_);

    path_ = findShortestPath(idx_start, idx_target_);
  }
  else {
    idx_start = path_[pIdx_closestNode_];
    std::vector<int> path_update = findShortestPath(idx_start, idx_target_);

    path_update.insert(path_update.begin(), path_.begin(), path_.begin() + pIdx_closestNode_ + 1);
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
  for (size_t i = 0; i < path_.size(); ++i) {
    auto [x, y] = Common::MapUtils::getPosFromMapIndex(path_[i], gridMetaData_);
    float distance = std::hypot(x - pos_x, y - pos_y);
    if (distance < dist_closestNode) {
      dist_closestNode = distance;
      pIdx_closestNode_ = i;
    }
  }
}

std::pair<float, float> Planner::calcSteering() {
  float pos_x = lastVehiclePose_->pose.position.x;
  float pos_y = lastVehiclePose_->pose.position.y;
  float phi = tf2::getYaw(lastVehiclePose_->pose.orientation);
  
  setClosestNode();

  // stanley controller
  auto [x_closestNode, y_closestNode] = Common::MapUtils::getPosFromMapIndex(path_[pIdx_closestNode_], gridMetaData_);

  float x_closestNodePrev = x_closestNode;
  float y_closestNodePrev = y_closestNode;
  float x_closestNodeNext = x_closestNode;
  float y_closestNodeNext = y_closestNode;

  if (pIdx_closestNode_ > 0) {
    std::tie(x_closestNodePrev, y_closestNodePrev) = Common::MapUtils::getPosFromMapIndex(path_[pIdx_closestNode_ - 1], gridMetaData_);
  }

  if (static_cast<size_t>(pIdx_closestNode_) < (path_.size() - 1)) {
    std::tie(x_closestNodeNext, y_closestNodeNext) = Common::MapUtils::getPosFromMapIndex(path_[pIdx_closestNode_ + 1], gridMetaData_);
  }

  float cte = (y_closestNode - pos_y) * std::cos(phi) - (x_closestNode - pos_x) * std::sin(phi);
  float phi_target = std::atan2(y_closestNodeNext - y_closestNodePrev, x_closestNodeNext - x_closestNodePrev);
  float speed = std::lerp(0, maxSpeed, std::clamp(
    (distAhead_ - minDist) / (maxSpeedDist - minDist), 0.0f, 1.0f));  
  
  float steering_angle = (phi_target - phi) + std::atan(gain_cte * cte / speed);

  return {speed, steering_angle};
}

std::vector<int> Planner::findShortestPath(int idx_state, int idx_target) {
  int width = gridMetaData_->width;
  int height = gridMetaData_->height;

  // Dijkstra Algorithm  
  std::vector<int8_t> occgrid = lastOccGrid_->data;
  int V = occgrid.size();

  // pq = {{distance, vertex}, ...}
  std::priority_queue<
    std::pair<float, int>, 
    std::vector<std::pair<float, int>>, 
    std::greater<std::pair<float, int>>> pq;

  std::vector<float> dist(V, INT_MAX);
  std::vector<int> parent(V, -1);

  // add source vertex to queue
  dist[idx_state] = 0;
  pq.emplace(0, idx_state);

  while (!pq.empty()) {
    // select closest vertex u from the queue
    auto top = pq.top();
    pq.pop();

    float d = top.first;  
    int u = top.second; 

    // stop when target node is found
    if (u == idx_target)
      break;

    if (d > dist[u])
        continue;

    // check distance to all neighbors v of u
    int ux = u % width, uy = u / width;
    for (int dy = -1; dy <= 1; ++dy) {
      for (int dx = -1; dx <= 1; ++dx) {
        if (!dx && !dy) continue;
        int vx = ux + dx;
        int vy = uy + dy;
        if (vx < 0 || vy < 0 || vx >= width || vy >= height) continue;
        int v = vy * width + vx;

        int8_t c = occgrid[v];
        if (c >= kBlocked) continue;

        float step = (dx && dy) ? 1.4142f : 1.0f;           
        float risk_weight = 1.0f; 
        step *= (1.0f + risk_weight * (static_cast<float>(c) / 100.0f));      

        // if distance to v through u is shorter, update distance and parent
        if (dist[u] + step < dist[v]) {
          dist[v] = dist[u] + step;
          parent[v] = u;
          pq.emplace(dist[v], v);
        }
      }
    }
  }

  // construct path
  std::vector<int> path;
  int v = idx_target;

  while (v != idx_state) {
    path.push_back(v);
    v = parent[v];
  }
  std::reverse(path.begin(), path.end());
  return path;
}


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Planner>());
  rclcpp::shutdown();
  return 0;
}