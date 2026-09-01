#pragma once
#include <yaml-cpp/yaml.h>
#include <vector>
#include <utility>

#include "rclcpp/rclcpp.hpp"

#include "car_msgs/msg/vehicle_state.hpp"
#include "car_msgs/msg/motion_control.hpp"
#include "car_msgs/msg/node_state.hpp"
#include "common/datatypes.hpp"
#include "common/basenode.hpp"
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <nav_msgs/msg/path.hpp>


class Planner : public BaseNode {
  public:
    Planner();
    VehicleState vehicleState_;
	
  private:
    std::pair<int, int> target_{};
    int idx_target_{};
    std::vector<std::vector<int>> adjList_;

    car_msgs::msg::NodeState::SharedPtr lastNodeState_;
    car_msgs::msg::VehicleState::SharedPtr lastVehicleState_;
    nav_msgs::msg::OccupancyGrid::SharedPtr lastOccGrid_;

  	rclcpp::Publisher<car_msgs::msg::MotionControl>::SharedPtr pub_motionControl_;
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pub_path_;
	
    rclcpp::Subscription<car_msgs::msg::VehicleState>::SharedPtr sub_vehicleState_;
    rclcpp::Subscription<car_msgs::msg::NodeState>::SharedPtr sub_nodeState_;
    rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr sub_occGrid_;


	void callback_vehicleState(const car_msgs::msg::VehicleState::SharedPtr msg);
  void callback_nodeState(const car_msgs::msg::NodeState::SharedPtr msg);
  void callback_occGrid(const nav_msgs::msg::OccupancyGrid::SharedPtr msg);
  void publish_motionControl();
  void publish_path();

  std::vector<std::vector<int>> buildAdjacentList();
  std::vector<int> findShortestPath(
    std::vector<int8_t>& occgrid, 
    int idx_state, 
    int idx_target);

};