#include <memory>
#include <cmath>
#include <chrono>
#include <yaml-cpp/yaml.h>


#include "rclcpp/rclcpp.hpp"
#include "common/config.hpp"

#include "recorder/recorder.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

Recorder::Recorder()
  : Node("recorder") {
    config_ = common::get_config();

    pub_histVehicleState_ = this->create_publisher<nav_msgs::msg::Path>(
        config_["topics"]["histVehicleState"].as<std::string>(), 10);
    pub_histVehicleStateAct_ = this->create_publisher<nav_msgs::msg::Path>(
        config_["topics"]["histVehicleStateAct"].as<std::string>(), 10);

    timer_ = this->create_wall_timer(500ms, std::bind(&Recorder::callback_histVehicleState, this));

    sub_vehicleState_ = create_subscription<car_msgs::msg::VehicleState>(
        config_["topics"]["vehicleState"].as<std::string>(), 10, std::bind(&Recorder::callback_vehicleState, this, _1));
    sub_vehicleStateAct_ = create_subscription<car_msgs::msg::VehicleState>(
        config_["topics"]["vehicleStateAct"].as<std::string>(), 10, std::bind(&Recorder::callback_vehicleStateAct, this, _1));
}

void Recorder::callback_vehicleState(const car_msgs::msg::VehicleState::SharedPtr msg) {
    latest_pose_.header.stamp = this->now();
    latest_pose_.header.frame_id = "map";
    latest_pose_.pose.position.x = msg->pos_x;
    latest_pose_.pose.position.y = msg->pos_y;
    latest_pose_.pose.position.z = 0.0;
}

void Recorder::callback_vehicleStateAct(const car_msgs::msg::VehicleState::SharedPtr msg) {
    latest_poseAct_.header.stamp = this->now();
    latest_poseAct_.header.frame_id = "map";
    latest_poseAct_.pose.position.x = msg->pos_x;
    latest_poseAct_.pose.position.y = msg->pos_y;
    latest_poseAct_.pose.position.z = 0.0;
}

void Recorder::callback_histVehicleState() {
    path_.header.frame_id = "map";
    path_.poses.push_back(latest_pose_);
    path_.header.stamp = latest_pose_.header.stamp;
    pub_histVehicleState_->publish(path_);
    
    pathAct_.header.frame_id = "map";
    pathAct_.poses.push_back(latest_poseAct_);
    pathAct_.header.stamp = latest_poseAct_.header.stamp;
    pub_histVehicleStateAct_->publish(pathAct_);
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Recorder>());
    rclcpp::shutdown();
    return 0;
}