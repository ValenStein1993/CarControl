#pragma once
#include <yaml-cpp/yaml.h>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "common/datatypes.hpp"
#include "car_msgs/msg/vehicle_state.hpp"
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>


constexpr float init_probOcc = 0.5f;

class Mapper : public rclcpp::Node {
  public:
    Mapper();
	
  private:
    YAML::Node config_{};
    car_msgs::msg::VehicleState::SharedPtr lastVehicleState_{};

  	rclcpp::TimerBase::SharedPtr timer_{};
    std::vector<float> occgrid_{};
    float init_logOdd_{};

    rclcpp::Subscription<car_msgs::msg::VehicleState>::SharedPtr sub_vehicleState_{};
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr sub_laserScan_{};
    rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr pub_occGrid_{};


    void callback_laserscan(const sensor_msgs::msg::LaserScan::SharedPtr msg);
    void callback_vehicleState(const car_msgs::msg::VehicleState::SharedPtr msg);
    void callback_map();

    int getMapIndexFromPos(float x, float y);
    void updateBinaryBayesFilter(int idx, float p);






    
    
};