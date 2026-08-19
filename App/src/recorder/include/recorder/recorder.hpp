#pragma once
#include <yaml-cpp/yaml.h>

#include "rclcpp/rclcpp.hpp"

#include "car_msgs/msg/vehicle_state.hpp"
#include "car_msgs/msg/motion_control.hpp"
#include "nav_msgs/msg/path.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "common/datatypes.hpp"

class Recorder : public rclcpp::Node {
  public:
    Recorder();
	
  private:
    YAML::Node config_{};

  	rclcpp::TimerBase::SharedPtr timer_{};
    geometry_msgs::msg::PoseStamped latest_pose_;
    geometry_msgs::msg::PoseStamped latest_poseAct_;
    nav_msgs::msg::Path path_;
    nav_msgs::msg::Path pathAct_;
    
  	rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pub_histVehicleState_{};
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pub_histVehicleStateAct_{};

    rclcpp::Subscription<car_msgs::msg::VehicleState>::SharedPtr sub_vehicleState_{};
    rclcpp::Subscription<car_msgs::msg::VehicleState>::SharedPtr sub_vehicleStateAct_{};

	void callback_vehicleState(const car_msgs::msg::VehicleState::SharedPtr msg);
	void callback_vehicleStateAct(const car_msgs::msg::VehicleState::SharedPtr msg);
  void callback_histVehicleState();

};