#pragma once
#include "rclcpp/rclcpp.hpp"

#include "car_msgs/msg/position.hpp"
#include "car_msgs/msg/steering.hpp"
#include "common/datatypes.hpp"

class Planner : public rclcpp::Node {
  public:
    Planner();
    Position pos_{};
	
  private:
  	rclcpp::TimerBase::SharedPtr timer_{};
  	rclcpp::Publisher<car_msgs::msg::Steering>::SharedPtr pub_steering_{};
	
    rclcpp::Subscription<car_msgs::msg::Position>::SharedPtr sub_position_{};

	void callback_position(const car_msgs::msg::Position::SharedPtr msg);
  void callback_steering();

};