#pragma once
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
#include <sensor_msgs/msg/laser_scan.hpp>
#include <nav_msgs/msg/odometry.hpp>


constexpr int8_t kBlocked = 75;
constexpr float lookAhead = 0.1;
constexpr float maxSpeed = 0.1;
constexpr float maxSpeedDist = 1;
constexpr float minDist = 0.1;

class Planner : public BaseNode {
  public:
    Planner();
    VehicleState vehicleState_;
	
  private:

    std::pair<float, float> target_{};
    int idx_target_{};
    std::vector<int> path_;
    float distAhead_;

    car_msgs::msg::NodeState::SharedPtr lastNodeState_;
    nav_msgs::msg::Odometry::SharedPtr lastVehicleState_;
    nav_msgs::msg::OccupancyGrid::SharedPtr lastOccGrid_;

  	rclcpp::Publisher<car_msgs::msg::MotionControl>::SharedPtr pub_motionControl_;
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pub_path_;
	
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr sub_vehicleState_;
    rclcpp::Subscription<car_msgs::msg::NodeState>::SharedPtr sub_nodeState_;
    rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr sub_occGrid_;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr sub_laserScan_;


    void callback_vehicleState(const nav_msgs::msg::Odometry::SharedPtr msg);
    void callback_nodeState(const car_msgs::msg::NodeState::SharedPtr msg);
    void callback_occGrid(const nav_msgs::msg::OccupancyGrid::SharedPtr msg);
    void callback_laserscan(const sensor_msgs::msg::LaserScan::SharedPtr msg);

    void publish_motionControl();
    void publish_path();

    void findShortestPath(int idx_state, int idx_target);
    bool checkVehicleSpace(const std::vector<int8_t>& occgrid, int vx, int vy, int dx, int dy);

};