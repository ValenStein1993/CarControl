#pragma once
#include <vector>
#include <utility>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>

#include "rclcpp/rclcpp.hpp"

#include "car_msgs/msg/vehicle_state.hpp"
#include "car_msgs/msg/motion_control.hpp"
#include "car_msgs/msg/node_state.hpp"
#include "car_msgs/msg/debug_controller.hpp"
#include "common/basenode.hpp"
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <nav_msgs/msg/path.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav_msgs/msg/map_meta_data.hpp>
#include "common/datatypes.hpp"


constexpr float maxSpeed = 0.02;
constexpr float maxSpeedDist = 0.3;
constexpr float minDist = 0.1;
constexpr float gain_cte = 2.0;


class Controller : public BaseNode {
  public:
    Controller();
	
  private:

    float distAhead_;
    GridNode closestNode_;

    car_msgs::msg::DebugController debugMsg_;
    geometry_msgs::msg::PoseStamped::SharedPtr lastVehiclePose_;
    sensor_msgs::msg::LaserScan::SharedPtr lastLaserScan_;
    nav_msgs::msg::Path::SharedPtr lastPath_;

    rclcpp::Publisher<car_msgs::msg::DebugController>::SharedPtr pub_debug_;
  	rclcpp::Publisher<car_msgs::msg::MotionControl>::SharedPtr pub_motionControl_;
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr pub_closestNode_;

    std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
    std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
	
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr sub_vehiclePose_;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr sub_laserScan_;
    rclcpp::Subscription<nav_msgs::msg::Path>::SharedPtr sub_path_;


    void callback_vehiclePose(const geometry_msgs::msg::PoseStamped::SharedPtr msg);
    void callback_path(const nav_msgs::msg::Path::SharedPtr msg);
    void callback_laserscan(const sensor_msgs::msg::LaserScan::SharedPtr msg);

    void publish_debugMsg();
    void publish_motionControl();
    void publish_closestNode();

    void setClosestNode();
    std::pair<float, float> calcSteering();

};