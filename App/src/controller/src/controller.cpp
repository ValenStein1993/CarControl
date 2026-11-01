#include <memory>
#include <cmath>
#include <chrono>
#include <queue>
#include <vector>
#include <climits>
#include <utility>
#include <numbers>
#include <algorithm>
#include <map>
#include <tf2/utils.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

#include "controller/controller.hpp"
#include "rclcpp/rclcpp.hpp"
#include "car_msgs/msg/vehicle_state.hpp"
#include "car_msgs/msg/motion_control.hpp"
#include <sensor_msgs/msg/laser_scan.hpp>
#include <geometry_msgs/msg/point.hpp>
#include "common/config.hpp"
#include "common/map_utils.hpp"
#include "common/config_app.hpp"
#include "common/datatypes.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

Controller::Controller()
  : BaseNode("controller"),
    closestNode_{0.0f, 0.0f, 0.0f, -1, -1} {

  if (debug_) {
    add_timer(100ms, &Controller::publish_debugMsg);
  }

  pub_debug_ = create_publisher<car_msgs::msg::DebugController>(
    static_cast<std::string>(config_topics_debugController), 10);
  pub_motionControl_ = create_publisher<car_msgs::msg::MotionControl>(
    static_cast<std::string>(config_topics_motionControl), 10);

  sub_vehiclePose_ = create_subscription<geometry_msgs::msg::PoseStamped>(
    static_cast<std::string>(config_topics_poseCrtgrphr), 10, 
    std::bind(&Controller::callback_vehiclePose, this, _1));
  sub_path_ = create_subscription<nav_msgs::msg::Path>(
    static_cast<std::string>(config_topics_globalPath), 10, 
    std::bind(&Controller::callback_path, this, _1));
  sub_laserScan_ = create_subscription<sensor_msgs::msg::LaserScan>(
    static_cast<std::string>(config_topics_laserScan), 10, 
    std::bind(&Controller::callback_laserscan, this, _1));
}

void Controller::callback_vehiclePose(const geometry_msgs::msg::PoseStamped::SharedPtr msg) {
  lastVehiclePose_ = msg;
  publish_motionControl();
}

void Controller::callback_laserscan(const sensor_msgs::msg::LaserScan::SharedPtr msg) {
  lastLaserScan_ = msg;
  distAhead_ = msg->ranges[0.5 * msg->ranges.size()];
}

void Controller::callback_path(const nav_msgs::msg::Path::SharedPtr msg) {
  lastPath_ = msg;
  publish_motionControl();
}

void Controller::publish_motionControl() 
{

  if (!lastVehiclePose_) {
    RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000, "Cannot plan motion: Vehicle pose is unavailable.");
    return;
  }

  if (!lastPath_) {
    RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000, "Cannot plan motion: Vehicle path is unavailable.");
    return;
  }

  auto [speed, steering_angle] = calcSteering();
  float yaw_rate = (speed / config_vehicle_wheelbase) * std::tan(steering_angle);

  car_msgs::msg::MotionControl msg;
  msg.yaw_rate = yaw_rate; 
  msg.speed = speed; 

  pub_motionControl_->publish(msg);
}

void Controller::publish_debugMsg() {
  debugMsg_.header.stamp = get_clock()->now();
  pub_debug_->publish(debugMsg_);
}

void Controller::setClosestNode() {
  float pos_x = lastVehiclePose_->pose.position.x;
  float pos_y = lastVehiclePose_->pose.position.y;
  
  float dist_closestNode = std::numeric_limits<float>::max();
  int init_search;
  if (closestNode_.idx == -1) {
    init_search = 0;
  }
  else {
    init_search = closestNode_.idx;
  }

  for (size_t i = init_search; i < lastPath_->poses.size(); ++i) {
    geometry_msgs::msg::Point p = lastPath_->poses[i].pose.position;
    float distance = std::hypot(p.x - pos_x, p.y - pos_y);
    if (distance < dist_closestNode) {
      dist_closestNode = distance;
      closestNode_ = {static_cast<float>(p.x), static_cast<float>(p.y), 0.0f, -1, static_cast<int>(i)};
    }
  }

  float x_pPrev = closestNode_.x;
  float y_pPrev = closestNode_.y;
  float x_pNext = closestNode_.x;
  float y_pNext = closestNode_.y;

  if (closestNode_.idx > 0) {
    x_pPrev = lastPath_->poses[closestNode_.idx - 1].pose.position.x;
    y_pPrev = lastPath_->poses[closestNode_.idx - 1].pose.position.y;
  }

  if (static_cast<size_t>(closestNode_.idx) < (lastPath_->poses.size() - 1)) {
    x_pNext = lastPath_->poses[closestNode_.idx + 1].pose.position.x;
    y_pNext = lastPath_->poses[closestNode_.idx + 1].pose.position.y;
  }

  closestNode_.theta = std::atan2(y_pNext - y_pPrev, x_pNext - x_pPrev);
}

std::pair<float, float> Controller::calcSteering() {
  float pos_x = lastVehiclePose_->pose.position.x;
  float pos_y = lastVehiclePose_->pose.position.y;
  float pos_th = tf2::getYaw(lastVehiclePose_->pose.orientation);
  
  setClosestNode();

  // stanley controller
  float cte = (pos_y - closestNode_.y) * std::cos(closestNode_.theta) - (pos_x - closestNode_.x) * std::sin(closestNode_.theta);
  float speed = std::lerp(0, maxSpeed, std::clamp(
    (distAhead_ - minDist) / (maxSpeedDist - minDist), 0.0f, 1.0f));  
  float heading_error = closestNode_.theta - pos_th;
  float phi = std::clamp(
    static_cast<float>(heading_error + std::atan2(gain_cte * -cte ,(speed + 0.001))),
    -config_vehicle_max_steering, 
    config_vehicle_max_steering);

  float yaw_rate = (speed / config_vehicle_wheelbase) * std::tan(phi);

  if (debug_) {
    debugMsg_.yaw_rate = yaw_rate;
    debugMsg_.speed = speed;
    debugMsg_.steering_angle = phi;
    debugMsg_.pdx_cnode = closestNode_.idx;
    debugMsg_.cte = std::atan(gain_cte * cte / speed);
    debugMsg_.heading_error = heading_error;
  }
  return {speed, phi};
}



int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Controller>());
  rclcpp::shutdown();
  return 0;
}