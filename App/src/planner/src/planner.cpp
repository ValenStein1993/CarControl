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
  : BaseNode("planner") {

  declare_parameter<float>("x_target", 0.0f);
	declare_parameter<float>("y_target", 0.0f);

  get_parameter("x_target", target_.first);
  get_parameter("y_target", target_.second);

  add_timer(500ms, &Planner::publish_motionControl);
  add_timer(500ms, &Planner::publish_path);

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

void Planner::callback_vehiclePose(const geometry_msgs::msg::PoseStamped::SharedPtr msg) 
{
  lastVehiclePose_ = msg;
}

void Planner::callback_occGrid(const nav_msgs::msg::OccupancyGrid::SharedPtr msg) 
{
  lastOccGrid_ = msg;
  gridMetaData_ = &(msg->info);

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


  float pos_x = lastVehiclePose_->pose.position.x;
  float pos_y = lastVehiclePose_->pose.position.y;
  float phi = tf2::getYaw(lastVehiclePose_->pose.orientation);
  
  float min_distance = std::numeric_limits<float>::max();
  int idx_minDistance = -1;

  // get closest grid node to current position
  for (size_t i = 0; i < path_.size(); ++i) {
    auto [x, y] = Common::MapUtils::getPosFromMapIndex(path_[i], gridMetaData_);
    float distance = std::hypot(x - pos_x, y - pos_y);
    if (distance < min_distance) {
      min_distance = distance;
      idx_minDistance = i;
    }
  }

  // find lookahead to closest node
  size_t idx_lookAhead;
  float x_lookAhead, y_lookAhead;
  auto [x_minDistance, y_minDistance] = Common::MapUtils::getPosFromMapIndex(path_[idx_minDistance], gridMetaData_);
  for (idx_lookAhead = idx_minDistance; idx_lookAhead < path_.size(); ++idx_lookAhead) {
    std::tie(x_lookAhead, y_lookAhead) = Common::MapUtils::getPosFromMapIndex(path_[idx_lookAhead], gridMetaData_);
    float distance = std::hypot(x_lookAhead - x_minDistance, y_lookAhead - y_minDistance);
    if (distance > lookAhead) break;
  }

  // pure pursuit algorithm
  float dx_global = x_lookAhead - pos_x;
  float dy_global = y_lookAhead - pos_y;
  float yaw = phi;

  float dx_body =  std::cos(yaw) * dx_global + std::sin(yaw) * dy_global;
  float dy_body = -std::sin(yaw) * dx_global + std::cos(yaw) * dy_global;

  float speed = std::lerp(0, maxSpeed, std::clamp(
    (distAhead_ - minDist) / (maxSpeedDist - minDist), 0.0f, 1.0f));
  float l = std::hypot(dx_body, dy_body);      
  float curvature = 2.0f * dy_body / (l * l); 
  float yaw_rate = speed * curvature;

  car_msgs::msg::MotionControl msg;
  msg.yaw_rate = yaw_rate; 
  msg.speed = speed; 

  pub_motionControl_->publish(msg);
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

  int idx_pose = Common::MapUtils::getMapIndexFromPos(
    lastVehiclePose_->pose.position.x, 
    lastVehiclePose_->pose.position.y, 
    gridMetaData_);
  findShortestPath(idx_pose, idx_target_);

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

void Planner::findShortestPath(int idx_state, int idx_target) {
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
        // check space around vehicle
        if (!checkVehicleSpace(occgrid, vx, vy, dx, dy)) continue;

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
  path_ = path;
}

bool Planner::checkVehicleSpace(const std::vector<int8_t>& occgrid, int vx, int vy, int dx, int dy) {
  int vvx = vx, vvx_ = vx;
  int vvy = vy, vvy_ = vy;

  while (true) {
    if (dx) vvy += dx, vvy_ -= dx;
    if (dy) vvx -= dy, vvx_ += dy;

    if (!Common::MapUtils::checkGridBoundries(vvx, vvy, gridMetaData_)) return false;
    if (!Common::MapUtils::checkGridBoundries(vvx_, vvy_, gridMetaData_)) return false;

    int vv = vvy * gridMetaData_->width + vvx;
    int vv_ = vvy_ * gridMetaData_->width + vvx_;
    if ((occgrid[vv] > kBlocked) | (occgrid[vv_] > kBlocked)) return false;

    float dist = gridMetaData_->resolution * std::hypot(vy - vvy, vx - vvx);
    // stop, if covered distance is greater than half width (plus buffer)
    if (dist > (0.6 * config_vehicle_wheeltrack)) break;
  }
    return true;
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Planner>());
  rclcpp::shutdown();
  return 0;
}