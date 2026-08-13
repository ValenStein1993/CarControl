#pragma once
#include "rclcpp/rclcpp.hpp"

#include "car_msgs/msg/vehicle_state.hpp"
#include "car_msgs/msg/motion_control.hpp"
#include "common/datatypes.hpp"

class Planner : public rclcpp::Node {
  public:
    Planner();
    VehicleState vehicleState_{};
	
  private:
  	rclcpp::TimerBase::SharedPtr timer_{};
  	rclcpp::Publisher<car_msgs::msg::MotionControl>::SharedPtr pub_motionControl_{};
	
    rclcpp::Subscription<car_msgs::msg::VehicleState>::SharedPtr sub_vehicleState_{};

	void callback_vehicleState(const car_msgs::msg::VehicleState::SharedPtr msg);
  void callback_motionControl();

};