#include <memory>
#include <cmath>
#include <chrono>
#include <queue>
#include <vector>
#include <climits>
#include <utility>
#include <numbers>

#include "planner/planner.hpp"
#include "rclcpp/rclcpp.hpp"
#include "car_msgs/msg/vehicle_state.hpp"
#include "car_msgs/msg/motion_control.hpp"
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

  idx_target_ = Common::MapUtils::getMapIndexFromPos(target_.first, target_.second);

  add_timer(500ms, &Planner::publish_motionControl);
  add_timer(500ms, &Planner::publish_path);

  pub_motionControl_ = create_publisher<car_msgs::msg::MotionControl>(
    static_cast<std::string>(config_topics_motionControl), 10);
  pub_path_ = create_publisher<nav_msgs::msg::Path>(
    static_cast<std::string>(config_topics_globalPath), 10);

  sub_vehicleState_ = create_subscription<car_msgs::msg::VehicleState>(
    static_cast<std::string>(config_topics_vehicleStateEkf), 10, 
    std::bind(&Planner::callback_vehicleState, this, _1));
  sub_nodeState_ = create_subscription<car_msgs::msg::NodeState>(
    static_cast<std::string>(config_topics_nodeState), 10, 
    std::bind(&Planner::callback_nodeState, this, _1));
  sub_occGrid_ = create_subscription<nav_msgs::msg::OccupancyGrid>(
    static_cast<std::string>(config_topics_occupancyGrid), 10, 
    std::bind(&Planner::callback_occGrid, this, _1));
}

void Planner::callback_vehicleState(const car_msgs::msg::VehicleState::SharedPtr msg) 
{
  lastVehicleState_ = msg;
}

void Planner::callback_nodeState(const car_msgs::msg::NodeState::SharedPtr msg) 
{
  lastNodeState_ = msg;
}

void Planner::callback_occGrid(const nav_msgs::msg::OccupancyGrid::SharedPtr msg) 
{
  lastOccGrid_ = msg;
}


void Planner::publish_motionControl() 
{
  if (!lastNodeState_ || !lastNodeState_->localizer_is_ready) {
    return;
  }
  
  int lookAhead = 0.1;
  float min_distance = std::numeric_limits<float>::max();
  int idx_minDistance = -1;

  // get closest grid node to current position
  for (size_t i = 0; i < path_.size(); ++i) {
    auto [x, y] = Common::MapUtils::getPosFromMapIndex(path_[i]);
    float distance = std::hypot(x - lastVehicleState_->pos_x, y - lastVehicleState_->pos_y);
    if (distance < min_distance) {
      min_distance = distance;
      idx_minDistance = i;
    }
  }

  // find lookahead to closest node
  size_t idx_lookAhead;
  float x_lookAhead, y_lookAhead;
  auto [x_minDistance, y_minDistance] = Common::MapUtils::getPosFromMapIndex(path_[idx_minDistance]);
  for (idx_lookAhead = idx_minDistance; idx_lookAhead < path_.size(); ++idx_lookAhead) {
    std::tie(x_lookAhead, y_lookAhead) = Common::MapUtils::getPosFromMapIndex(path_[idx_lookAhead]);
    float distance = std::hypot(x_lookAhead - x_minDistance, y_lookAhead - y_minDistance);
    if (distance > lookAhead) break;
  }

  // pure pursuit algorithm
  float dx_global = x_lookAhead - lastVehicleState_->pos_x;
  float dy_global = y_lookAhead - lastVehicleState_->pos_y;
  float yaw = lastVehicleState_->yaw;

  float dx_body =  std::cos(yaw) * dx_global + std::sin(yaw) * dy_global;
  float dy_body = -std::sin(yaw) * dx_global + std::cos(yaw) * dy_global;

  float speed = 0.05;
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
  if (!lastVehicleState_ || !lastOccGrid_) {
    return;
  }

  int idx_state = Common::MapUtils::getMapIndexFromPos(lastVehicleState_->pos_x, lastVehicleState_->pos_y);
  path_ = findShortestPath(idx_state, idx_target_);

  nav_msgs::msg::Path pathMsg;
  pathMsg.header.stamp = get_clock()->now();
  pathMsg.header.frame_id = config_frames_ekf_odom;

  for (int idx : path_) {
    auto [x, y] = Common::MapUtils::getPosFromMapIndex(idx);

    geometry_msgs::msg::PoseStamped pose;
    pose.pose.position.x = x;
    pose.pose.position.y = y;
    pathMsg.poses.push_back(pose);
  }
  pub_path_->publish(pathMsg);
}

std::vector<int> Planner::findShortestPath(int idx_state, int idx_target) 
{
  int width = config_occgrid_width;
  int height = config_occgrid_height;

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
        if (!checkVehicleSpace(vx, vy, dx, dy)) continue;

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

bool Planner::checkVehicleSpace(int vx, int vy, int dx, int dy) {
  std::vector<int8_t> occgrid = lastOccGrid_->data;
  int vvx = vx, vvx_ = vx;
  int vvy = vy, vvy_ = vy;

  while (true) {
    if (dx) vvy += dx, vvy_ -= dx;
    if (dy) vvx -= dy, vvx_ += dy;

    if (!Common::MapUtils::checkGridBoundries(vvx, vvy)) return false;
    if (!Common::MapUtils::checkGridBoundries(vvx_, vvy_)) return false;

    int vv = vvy * config_occgrid_width + vvx;
    int vv_ = vvy_ * config_occgrid_width + vvx_;
    if ((occgrid[vv] > kBlocked) | (occgrid[vv_] > kBlocked)) return false;

    float dist = config_occgrid_resolution * std::hypot(vy - vvy, vx - vvx);
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