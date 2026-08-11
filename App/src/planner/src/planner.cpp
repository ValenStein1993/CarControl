#include <memory>
#include <cmath>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "car_msgs/msg/position.hpp"
#include "car_msgs/msg/steering.hpp"


#include "planner/planner.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

Planner::Planner()
  : Node("planner") {

  pub_steering_ = this->create_publisher<car_msgs::msg::Steering>("/steering", 10);
  timer_ = this->create_wall_timer(500ms, std::bind(&Planner::callback_steering, this));

  sub_position_ = create_subscription<car_msgs::msg::Position>(
    "/position", 10, std::bind(&Planner::callback_position, this, _1));
}

void Planner::callback_position(const car_msgs::msg::Position::SharedPtr msg) {
  // Implementation for position callback
}

void Planner::callback_steering() {
  car_msgs::msg::Steering msg;
  msg.steering_angle = 5.0; // Example value, replace with actual logic
  msg.speed = 2.0; // Example value, replace with actual logic

  pub_steering_->publish(msg);
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Planner>());
  rclcpp::shutdown();
  return 0;
}