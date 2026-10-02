#pragma once
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "common/datatypes.hpp"
#include "common/basenode.hpp"
#include "car_msgs/msg/vehicle_state.hpp"
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <nav_msgs/msg/odometry.hpp>


constexpr float init_probOcc = 0.5f;

class Mapper : public BaseNode {
  public:
    Mapper();
	
  private:
    nav_msgs::msg::Odometry::SharedPtr lastVehicleState_{};

  	rclcpp::TimerBase::SharedPtr timer_{};
    std::vector<float> occgrid_{};
    std::vector<bool> updateOccgrid_{};
    float init_logOdd_{};

    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr sub_vehicleState_{};
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr sub_laserScan_{};
    rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr pub_occGrid_{};


    void callback_laserscan(const sensor_msgs::msg::LaserScan::SharedPtr msg);
    void callback_vehicleState(const nav_msgs::msg::Odometry::SharedPtr msg);
    void publish_map();






    
    
};