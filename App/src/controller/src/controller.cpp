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

  add_timer(100ms, &Controller::publish_closestNode);

  pub_debug_ = create_publisher<car_msgs::msg::DebugController>(
    static_cast<std::string>(config_topics_debugController), 10);
  pub_motionControl_ = create_publisher<car_msgs::msg::MotionControl>(
    static_cast<std::string>(config_topics_motionControl), 10);
  pub_closestNode_ = create_publisher<geometry_msgs::msg::PoseStamped>(
    static_cast<std::string>(config_topics_closestNode), 10);

  sub_vehiclePose_ = create_subscription<geometry_msgs::msg::PoseStamped>(
    static_cast<std::string>(config_topics_poseCrtgrphr), 10, 
    std::bind(&Controller::callback_vehiclePose, this, _1));
  sub_path_ = create_subscription<nav_msgs::msg::Path>(
    static_cast<std::string>(config_topics_globalPath), 10, 
    std::bind(&Controller::callback_path, this, _1));
  sub_laserScan_ = create_subscription<sensor_msgs::msg::LaserScan>(
    static_cast<std::string>(config_topics_laserScan), 10, 
    std::bind(&Controller::callback_laserscan, this, _1));

  tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
}

void Controller::callback_vehiclePose(const geometry_msgs::msg::PoseStamped::SharedPtr msg) {

  std::string vehicle_base_frame = "base_link";
  std::string front_axle_frame = "front_axle_link";

  if (!tf_buffer_->canTransform(vehicle_base_frame, front_axle_frame, tf2::TimePointZero)) {
    return;
  }

  const auto base_to_front_axle = tf_buffer_->lookupTransform(
      vehicle_base_frame, front_axle_frame, tf2::TimePointZero);

  tf2::Transform map_to_chassis;
  tf2::fromMsg(msg->pose, map_to_chassis);

  tf2::Transform chassis_to_front_axle_tf;
  tf2::fromMsg(base_to_front_axle.transform, chassis_to_front_axle_tf);

  const tf2::Transform map_to_front_axle = map_to_chassis * chassis_to_front_axle_tf;

  geometry_msgs::msg::PoseStamped front_axle_pose;
  front_axle_pose.header = msg->header;
  front_axle_pose.pose.position.x = map_to_front_axle.getOrigin().x();
  front_axle_pose.pose.position.y = map_to_front_axle.getOrigin().y();
  front_axle_pose.pose.position.z = map_to_front_axle.getOrigin().z();
  front_axle_pose.pose.orientation = tf2::toMsg(map_to_front_axle.getRotation());
  lastVehiclePose_ = std::make_shared<geometry_msgs::msg::PoseStamped>(front_axle_pose);

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

void Controller::publish_closestNode() {
  if (!lastPath_) {
    RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000, "Cannot publish closest node: Vehicle path is unavailable.");
    return;
  }

  geometry_msgs::msg::PoseStamped msg;
  msg.header.stamp = get_clock()->now();
  msg.header.frame_id = lastPath_->header.frame_id;
  msg.pose.position.x = closestNode_.x;
  msg.pose.position.y = closestNode_.y;
  msg.pose.position.z = 0.0;
  
  tf2::Quaternion q;
  q.setRPY(0, 0, closestNode_.theta);
  msg.pose.orientation = tf2::toMsg(q);

  pub_closestNode_->publish(msg);
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
  float cte_error = std::atan2(gain_cte * -cte ,(speed + 0.001));
  float phi = std::clamp(
    static_cast<float>(heading_error + cte_error),
    -config_vehicle_max_steering, 
    config_vehicle_max_steering);

  float yaw_rate = (speed / config_vehicle_wheelbase) * std::tan(phi);

  if (debug_) {
    debugMsg_.yaw_rate = yaw_rate;
    debugMsg_.yaw = pos_th;
    debugMsg_.cn_yaw = closestNode_.theta;
    debugMsg_.speed = speed;
    debugMsg_.steering_angle = phi;
    debugMsg_.pdx_cnode = closestNode_.idx;
    debugMsg_.cte = cte_error;
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