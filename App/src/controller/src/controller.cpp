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
#include "common/utils.hpp"
#include "common/config_app.hpp"
#include "common/datatypes.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

using Common::MathUtils::wrapAngle;

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
  const int idx = closestNode_.idx;
  bool keepIdx = false;
  if (lastPath_ && idx >= 0 &&
      static_cast<size_t>(idx) < lastPath_->poses.size() &&
      static_cast<size_t>(idx) + 1 < msg->poses.size()) {
    const auto& a = lastPath_->poses[idx].pose.position;
    const auto& b = msg->poses[idx].pose.position;
    keepIdx = std::hypot(a.x - b.x, a.y - b.y) < 1e-4;
  }
  lastPath_ = msg;
  if (!keepIdx) closestNode_.idx = -1;
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


int Controller::getDrivingDir(int i) const {
  const auto& a = lastPath_->poses[i].pose;
  const auto& b = lastPath_->poses[i + 1].pose.position;
  const double yaw = tf2::getYaw(a.orientation);
  // Dot product between yaw and vector to next point tells if forward or reverse direction 
  const double dot = (b.x - a.position.x) * std::cos(yaw) + (b.y - a.position.y) * std::sin(yaw);
  return dot >= 0.0 ? 1 : -1;
}

int Controller::getSegmentEnd(int first) const {
  // last segment index before the next direction change
  const int nSeg = static_cast<int>(lastPath_->poses.size()) - 1;
  int dir = 0;
  int last = first;
  for (int i = first; i < nSeg; ++i) {
    const int d = getDrivingDir(i);
    if (dir == 0) dir = d;
    else if (d != dir) break;
    last = i;
  }
  return last;
}

std::optional<PathProjection> Controller::projectOnPath(float pos_x, float pos_y, int first, int last) const {
  // projects (pos_x, pos_y) onto segments [first, last] of the path
  const auto& poses = lastPath_->poses;

  float bestDist = std::numeric_limits<float>::max();
  std::optional<PathProjection> best;

  for (int i = first; i <= last; ++i) {

    const float ax = poses[i].pose.position.x;
    const float ay = poses[i].pose.position.y;
    const float dx = poses[i + 1].pose.position.x - ax;
    const float dy = poses[i + 1].pose.position.y - ay;
    const float len2 = dx * dx + dy * dy;

    const float t = std::clamp(((pos_x - ax) * dx + (pos_y - ay) * dy) / len2, 0.0f, 1.0f);
    const float qx = ax + t * dx;
    const float qy = ay + t * dy;
    const float dist = std::hypot(pos_x - qx, pos_y - qy);

    if (dist < bestDist) {
      bestDist = dist;
      const float yaw_a = tf2::getYaw(poses[i].pose.orientation);
      const float yaw_b = tf2::getYaw(poses[i + 1].pose.orientation);
      best = PathProjection{qx, qy, std::atan2(dy, dx),
        wrapAngle(yaw_a + t * wrapAngle(yaw_b - yaw_a)), t, i, getDrivingDir(i)};
    }
  }
  return best;
}

std::pair<float, float> Controller::calcSteering() {
  const int nSeg = static_cast<int>(lastPath_->poses.size()) - 1;
  if (nSeg < 1) {
    RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000, "Path has less than 2 points: stopping.");
    return {0.0f, 0.0f};
  }

  const float x_front = lastVehiclePose_->pose.position.x;
  const float y_front = lastVehiclePose_->pose.position.y;
  const float yaw = tf2::getYaw(lastVehiclePose_->pose.orientation);
  const float x_rear = x_front - config_vehicle_wheelbase * std::cos(yaw);
  const float y_rear = y_front - config_vehicle_wheelbase * std::sin(yaw);

  auto projectRun = [&](int first) {
    const int last = getSegmentEnd(first);
    auto p = projectOnPath(x_front, y_front, first, last);
    //if (p && p->dir == -1) p = projectOnPath(x_rear, y_rear, first, last);
    return std::make_pair(p, last);
  };

  int first = std::clamp(closestNode_.idx, 0, nSeg - 1);
  auto [proj, last] = projectRun(first);

  // reference point passed the goal or end of the segment
  while (proj && proj->idx == last && proj->t >= 1.0f) {
    if (last + 1 >= nSeg) {
      closestNode_ = {proj->x, proj->y, proj->heading, 0.0f, proj->idx};
      RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000, "Goal reached: stopping.");
      return {0.0f, 0.0f};
    }
    first = last + 1;
    std::tie(proj, last) = projectRun(first);
  }

  closestNode_ = {proj->x, proj->y, proj->heading, 0.0f, proj->idx};
  const int dir = proj->dir;
  const float x_ref = dir == 1 ? x_front : x_rear;
  const float y_ref = dir == 1 ? y_front : y_rear;

  const float cte = (y_ref - proj->y) * std::cos(proj->tangent) -
    (x_ref - proj->x) * std::sin(proj->tangent);

  const float heading_error = wrapAngle(proj->heading - yaw);
  const float cte_error = std::atan2(-gain_cte * cte, soft_cte + maxSpeed);

  float phi = heading_error + cte_error;
  if (dir == -1) phi = -phi;
  phi = std::clamp(phi, -config_vehicle_max_steering, config_vehicle_max_steering);

  const float speed = dir * maxSpeed;
  const float yaw_rate = (speed / config_vehicle_wheelbase) * std::tan(phi);

  if (debug_) {
    debugMsg_.yaw_rate = yaw_rate;
    debugMsg_.yaw = yaw;
    debugMsg_.cn_yaw = proj->heading;
    debugMsg_.speed = speed;
    debugMsg_.steering_angle = phi;
    debugMsg_.pdx_cnode = proj->idx;
    debugMsg_.cte = cte;
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