#include <memory>
#include <cmath>
#include <chrono>


#include "rclcpp/rclcpp.hpp"
#include "common/config.hpp"

#include "recorder/recorder.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

Recorder::Recorder()
  : BaseNode("recorder") {

      add_timer(500ms, &Recorder::callback_histVehicleState);

    pub_histVehicleStateEkf_ = this->create_publisher<nav_msgs::msg::Path>(
        static_cast<std::string>(config_topics_histVehicleStateEkf), 10);
    pub_histVehicleStateCsm_ = this->create_publisher<nav_msgs::msg::Path>(
        static_cast<std::string>(config_topics_histVehicleStateCsm), 10);
    pub_histVehicleStateAct_ = this->create_publisher<nav_msgs::msg::Path>(
        static_cast<std::string>(config_topics_histVehicleStateAct), 10);

    sub_vehicleStateEkf_ = create_subscription<nav_msgs::msg::Odometry>(
        static_cast<std::string>(config_topics_vehicleStateEkf), 10, 
        std::bind(&Recorder::callback_vehicleStateEkf, this, _1));
    sub_vehicleStateCsm_ = create_subscription<nav_msgs::msg::Odometry>(
        static_cast<std::string>(config_topics_vehicleStateCsm), 10, 
        std::bind(&Recorder::callback_vehicleStateCsm, this, _1));
    sub_vehicleStateAct_ = create_subscription<nav_msgs::msg::Odometry>(
        static_cast<std::string>(config_topics_vehicleStateAct), 10, 
        std::bind(&Recorder::callback_vehicleStateAct, this, _1));
}

void Recorder::callback_vehicleStateEkf(const nav_msgs::msg::Odometry::SharedPtr msg) {
    latest_poseEkf_.header.stamp = this->now();
    latest_poseEkf_.header.frame_id = static_cast<std::string>(config_frames_ekf_odom);
    latest_poseEkf_.pose.position.x = msg->pose.pose.position.x;
    latest_poseEkf_.pose.position.y = msg->pose.pose.position.y;
    latest_poseEkf_.pose.position.z = 0.0;
}

void Recorder::callback_vehicleStateCsm(const nav_msgs::msg::Odometry::SharedPtr msg) {
    latest_poseCsm_.header.stamp = this->now();
    latest_poseCsm_.header.frame_id = static_cast<std::string>(config_frames_csm_odom);
    latest_poseCsm_.pose.position.x = msg->pose.pose.position.x;
    latest_poseCsm_.pose.position.y = msg->pose.pose.position.y;
    latest_poseCsm_.pose.position.z = 0.0;
}

void Recorder::callback_vehicleStateAct(const nav_msgs::msg::Odometry::SharedPtr msg) {
    latest_poseAct_.header.stamp = this->now();
    latest_poseAct_.header.frame_id = static_cast<std::string>(config_frames_map);
    latest_poseAct_.pose.position.x = msg->pose.pose.position.x;
    latest_poseAct_.pose.position.y = msg->pose.pose.position.y;
    latest_poseAct_.pose.position.z = 0.0;
}

void Recorder::callback_histVehicleState() {
    pathEkf_.header.frame_id = static_cast<std::string>(config_frames_ekf_odom);
    pathEkf_.poses.push_back(latest_poseEkf_);
    pathEkf_.header.stamp = latest_poseEkf_.header.stamp;
    pub_histVehicleStateEkf_->publish(pathEkf_);

    pathCsm_.header.frame_id = static_cast<std::string>(config_frames_csm_odom);
    pathCsm_.poses.push_back(latest_poseCsm_);
    pathCsm_.header.stamp = latest_poseCsm_.header.stamp;
    pub_histVehicleStateCsm_->publish(pathCsm_);
    
    pathAct_.header.frame_id = static_cast<std::string>(config_frames_map);
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