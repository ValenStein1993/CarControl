#include <memory>
#include <cmath>
#include <chrono>
#include <yaml-cpp/yaml.h>


#include "rclcpp/rclcpp.hpp"
#include "car_msgs/msg/vehicle_state.hpp"
#include "car_msgs/msg/motion_control.hpp"
#include "common/config.hpp"

#include "planner/planner.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

Planner::Planner()
  : Node("planner") {

    config_ = common::get_config();

    pub_motionControl_ = this->create_publisher<car_msgs::msg::MotionControl>(config_["topics"]["motionControl"].as<std::string>(), 10);
    timer_ = this->create_wall_timer(500ms, std::bind(&Planner::callback_motionControl, this));

    sub_vehicleState_ = create_subscription<car_msgs::msg::VehicleState>(
      config_["topics"]["vehicleState"].as<std::string>(), 10, std::bind(&Planner::callback_vehicleState, this, _1));
    sub_nodeState_ = create_subscription<car_msgs::msg::NodeState>(
      config_["topics"]["nodeState"].as<std::string>(), 10, std::bind(&Planner::callback_nodeState, this, _1));
}

void Planner::callback_vehicleState(const car_msgs::msg::VehicleState::SharedPtr msg) {
  // Implementation for vehicle state callback
}

void Planner::callback_nodeState(const car_msgs::msg::NodeState::SharedPtr msg) {
  lastNodeState_ = msg;
}

void Planner::callback_motionControl() {
  if (!lastNodeState_ || !lastNodeState_->localizer_is_ready) {
    return;
  }
  
  car_msgs::msg::MotionControl msg;
  msg.yaw_rate = 0.1; // Example value, replace with actual logic
  msg.speed = 0.3; // Example value, replace with actual logic

  pub_motionControl_->publish(msg);
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Planner>());
  rclcpp::shutdown();
  return 0;
}