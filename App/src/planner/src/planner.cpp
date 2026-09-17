#include <memory>
#include <cmath>
#include <chrono>
#include <yaml-cpp/yaml.h>
#include <queue>
#include <vector>
#include <climits>
#include <utility>

#include "planner/planner.hpp"
#include "rclcpp/rclcpp.hpp"
#include "car_msgs/msg/vehicle_state.hpp"
#include "car_msgs/msg/motion_control.hpp"
#include "common/config.hpp"
#include "common/map_utils.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

Planner::Planner()
  : BaseNode("planner") 
{
    target_ = std::pair<int, int>{10, 10};
    idx_target_ = Common::MapUtils::getMapIndexFromPos(target_.first, target_.second, config_);

    adjList_ = buildAdjacentList();
    add_timer(500ms, &Planner::publish_motionControl);
    add_timer(500ms, &Planner::publish_path);

    pub_motionControl_ = create_publisher<car_msgs::msg::MotionControl>(
      config_["topics"]["motionControl"].as<std::string>(), 10);
    pub_path_ = create_publisher<nav_msgs::msg::Path>(
      config_["topics"]["globalPath"].as<std::string>(), 10);

    sub_vehicleState_ = create_subscription<car_msgs::msg::VehicleState>(
      config_["topics"]["vehicleStateEkf"].as<std::string>(), 10, std::bind(&Planner::callback_vehicleState, this, _1));
    sub_nodeState_ = create_subscription<car_msgs::msg::NodeState>(
      config_["topics"]["nodeState"].as<std::string>(), 10, std::bind(&Planner::callback_nodeState, this, _1));
    sub_occGrid_ = create_subscription<nav_msgs::msg::OccupancyGrid>(
      config_["topics"]["occupancyGrid"].as<std::string>(), 10, std::bind(&Planner::callback_occGrid, this, _1));
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
  
  car_msgs::msg::MotionControl msg;
  msg.yaw_rate = 0.0; // Example value, replace with actual logic
  msg.speed = 0.05; // Example value, replace with actual logic

  pub_motionControl_->publish(msg);
}

void Planner::publish_path()
{
  if (!lastVehicleState_ || !lastOccGrid_) {
    return;
  }
  
  int idx_state = Common::MapUtils::getMapIndexFromPos(
    lastVehicleState_->pos_x, 
    lastVehicleState_->pos_y, 
    config_);
  std::vector<int> path = findShortestPath(lastOccGrid_->data, idx_state, idx_target_);

  nav_msgs::msg::Path pathMsg;
  pathMsg.header.stamp = get_clock()->now();
  pathMsg.header.frame_id = config_["frames"]["odom"].as<std::string>();

  for (int idx : path) {
    auto [x, y] = Common::MapUtils::getPosFromMapIndex(idx, config_);
    geometry_msgs::msg::PoseStamped pose;
    pose.pose.position.x = x;
    pose.pose.position.y = y;
    pathMsg.poses.push_back(pose);
  }
  pub_path_->publish(pathMsg);
}

std::vector<std::vector<int>> Planner::buildAdjacentList() 
{
  int width = config_["occgrid"]["width"].as<int>();
  int height = config_["occgrid"]["height"].as<int>();
  int N = width * height;

  std::vector<std::vector<int>> adjList(N);

  for (int i = 0; i < N; i++) {
    adjList[i].reserve(4);

    int row = i / width;
    int col = i % width;

    if (row > 0) {
      adjList[i].push_back((row - 1) * width + col);
    }

    if (row < (height - 1)) {
      adjList[i].push_back((row + 1) * width + col);
    }

    if (col > 0) {
      adjList[i].push_back(i - 1);
    }

    if (col < (width - 1)) {
      adjList[i].push_back(i + 1);
    }
  }
  return adjList;
}

std::vector<int> Planner::findShortestPath(
  std::vector<int8_t>& occgrid, 
  int idx_state, 
  int idx_target) 
{
  // Dijkstra Algorithm  
  int V = occgrid.size();

  // pq = {{distance, vertex}, ...}
  std::priority_queue<
    std::pair<int, int>, 
    std::vector<std::pair<int, int>>, 
    std::greater<std::pair<int, int>>> pq;

  std::vector<int> dist(V, INT_MAX);
  std::vector<int> parent(V, -1);

  // add source vertex to queue
  dist[idx_state] = 0;
  pq.emplace(0, idx_state);

  while (!pq.empty()) {
      auto top = pq.top();
      pq.pop();

      int d = top.first;  
      int u = top.second; 

      // stop when target node is found
      if (u == idx_target)
        break;

      if (d > dist[u])
          continue;

      for (int v : adjList_[u]) {
          int w = occgrid[v]; 

            RCLCPP_INFO(get_logger(), "u: %d, v: %d, w: %d", u, v, w);

          // update distance if shorter
          if (dist[u] + w < dist[v]) {
              dist[v] = dist[u] + w;   
              parent[v] = u;
              pq.emplace(dist[v], v);
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

  return path;
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Planner>());
  rclcpp::shutdown();
  return 0;
}