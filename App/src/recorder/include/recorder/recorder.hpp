#pragma once
#include "rclcpp/rclcpp.hpp"

#include "car_msgs/msg/vehicle_state.hpp"
#include "car_msgs/msg/motion_control.hpp"
#include "nav_msgs/msg/path.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include <nav_msgs/msg/odometry.hpp>
#include "common/datatypes.hpp"
#include "common/basenode.hpp"

class Recorder : public BaseNode {
  public:
    Recorder();
	
  private:
    geometry_msgs::msg::PoseStamped latest_poseEkf_;
    geometry_msgs::msg::PoseStamped latest_poseCsm_;
    geometry_msgs::msg::PoseStamped latest_poseAct_;
    nav_msgs::msg::Path pathEkf_;
    nav_msgs::msg::Path pathCsm_;
    nav_msgs::msg::Path pathAct_;
    
  	rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pub_histVehicleStateEkf_{};
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pub_histVehicleStateCsm_{};
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pub_histVehicleStateAct_{};

    rclcpp::Subscription<car_msgs::msg::VehicleState>::SharedPtr sub_vehicleStateEkf_{};
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr sub_vehicleStateCsm_{};
    rclcpp::Subscription<car_msgs::msg::VehicleState>::SharedPtr sub_vehicleStateAct_{};

	void callback_vehicleStateEkf(const car_msgs::msg::VehicleState::SharedPtr msg);
  void callback_vehicleStateCsm(const nav_msgs::msg::Odometry::SharedPtr msg);
	void callback_vehicleStateAct(const car_msgs::msg::VehicleState::SharedPtr msg);
  void callback_histVehicleState();

};