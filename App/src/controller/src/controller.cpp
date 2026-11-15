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
#include "car_msgs/msg/sensor_measurements.hpp"


using namespace std::chrono_literals;
using std::placeholders::_1;

using Common::MathUtils::wrapAngle;

Controller::Controller()
  : BaseNode("controller"),
    closestNode_{{0.0f, 0.0f, 0.0f}, -1} {

  if (debug_) {
    add_timer(100ms, &Controller::publish_debugMsg);
  }

  add_timer(100ms, &Controller::publish_closestNode);

  pub_debug_ = create_publisher<car_msgs::msg::DebugController>(
    static_cast<std::string>(config_topics_debugController), 10);
  pub_motionControl_ = create_publisher<car_msgs::msg::MotionControl>(
    static_cast<std::string>(config_topics_motionControl), 10);
  pub_closestNodeDisp_ = create_publisher<geometry_msgs::msg::PoseStamped>(
    static_cast<std::string>(config_topics_closestNodeDisp), 10);
  pub_closestNode_ = create_publisher<car_msgs::msg::PathNode>(
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
  sub_measurements_ = create_subscription<car_msgs::msg::SensorMeasurements>(
		static_cast<std::string>(config_topics_sensorMeasurements), 10,
		std::bind(&Controller::callback_measurements, this, _1));

  tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
}

void Controller::callback_vehiclePose(const geometry_msgs::msg::PoseStamped::SharedPtr msg) {
  const std::string vehicle_base_frame{config_frames_vehicle_chassis};
  const std::string rear_axle_frame{config_frames_vehicle_rear_axle};

  if (!tf_buffer_->canTransform(vehicle_base_frame, rear_axle_frame, tf2::TimePointZero)) {
    return;
  }

  const auto base_to_rear_axle = tf_buffer_->lookupTransform(
      vehicle_base_frame, rear_axle_frame, tf2::TimePointZero);

  tf2::Transform map_to_chassis;
  tf2::fromMsg(msg->pose, map_to_chassis);

  tf2::Transform chassis_to_rear_axle;
  tf2::fromMsg(base_to_rear_axle.transform, chassis_to_rear_axle);

  // the path is planned for the rear axle
  const tf2::Transform map_to_rear_axle = map_to_chassis * chassis_to_rear_axle;

  geometry_msgs::msg::PoseStamped rear_axle_pose;
  rear_axle_pose.header = msg->header;
  tf2::toMsg(map_to_rear_axle, rear_axle_pose.pose);
  lastVehiclePose_ = std::make_shared<geometry_msgs::msg::PoseStamped>(rear_axle_pose);

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

void Controller::callback_measurements(const car_msgs::msg::SensorMeasurements::SharedPtr msg) {
  steeringAngleAct_ = msg->cjmcu103_angle;
}

void Controller::publish_closestNode() {
  if (!lastPath_) {
    RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000, "Cannot publish closest node: Vehicle path is unavailable.");
    return;
  }

  geometry_msgs::msg::PoseStamped msg;
  msg.header.stamp = get_clock()->now();
  msg.header.frame_id = lastPath_->header.frame_id;
  msg.pose.position.x = closestNode_.pose.x;
  msg.pose.position.y = closestNode_.pose.y;
  msg.pose.position.z = 0.0;
  
  tf2::Quaternion q;
  q.setRPY(0, 0, closestNode_.pose.th);
  msg.pose.orientation = tf2::toMsg(q);

  pub_closestNodeDisp_->publish(msg);

  car_msgs::msg::PathNode pathNodeMsg;
  pathNodeMsg.header.stamp = get_clock()->now();
  pathNodeMsg.header.frame_id = lastPath_->header.frame_id;
  pathNodeMsg.x = closestNode_.pose.x;
  pathNodeMsg.y = closestNode_.pose.y;
  pathNodeMsg.th = closestNode_.pose.th;
  pathNodeMsg.idx = closestNode_.idx;

  pub_closestNode_->publish(pathNodeMsg);
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

int Controller::getSegmentEnd(int first, int dir) const {
  // last segment index before the next direction change
  const int nSeg = static_cast<int>(lastPath_->poses.size()) - 1;
  int last = first;
  for (int i = first; i < nSeg; ++i) {
    const int d = getDrivingDir(i);
    if (d != dir) break;
    last = i;
  }
  return last;
}

Pose Controller::trackedAxle(const geometry_msgs::msg::Pose& p, int dir) const {
  const float theta = tf2::getYaw(p.orientation);
  const float offset = (dir == 1) ? config_vehicle_wheelbase : 0.0f;
  return Pose{static_cast<float>(p.position.x) + offset * std::cos(theta),
              static_cast<float>(p.position.y) + offset * std::sin(theta),
              theta};
}

std::optional<PathProjection> Controller::projectOnPath(int first, int last, int dir) const {
  // Projects the tracked axle onto segments [first, last] of the path of that axle
  const auto& poses = lastPath_->poses;

  const Pose vehicle = trackedAxle(lastVehiclePose_->pose, dir);
  const float pos_x = vehicle.x;
  const float pos_y = vehicle.y;

  float bestDist = std::numeric_limits<float>::max();
  std::optional<PathProjection> best;

  for (int i = first; i <= last; ++i) {

    const Pose a = trackedAxle(poses[i].pose, dir);
    const Pose b = trackedAxle(poses[i + 1].pose, dir);
    const float ax = a.x;
    const float ay = a.y;
    const float bx = b.x;
    const float by = b.y;
    const float dx = bx - ax;
    const float dy = by - ay;
    const float len2 = dx * dx + dy * dy;
    if (len2 < 1e-10f) continue;  // duplicate points -> avoid division by zero

    const float t = std::clamp(((pos_x - ax) * dx + (pos_y - ay) * dy) / len2, 0.0f, 1.0f);
    const float qx = ax + t * dx;
    const float qy = ay + t * dy;
    const float dist = std::hypot(pos_x - qx, pos_y - qy);

    if (dist < bestDist) {
      bestDist = dist;
      best = PathProjection{qx, qy, std::atan2(dy, dx),
        wrapAngle(a.th + t * wrapAngle(b.th - a.th)), t, i, dir};
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

  const float yaw = tf2::getYaw(lastVehiclePose_->pose.orientation);

  auto projectRun = [&](int first) {
    const int dir = getDrivingDir(first);
    const int last = getSegmentEnd(first, dir);
    auto p = projectOnPath(first, last, dir);
    return std::make_pair(p, last);
  };

  int first = std::clamp(closestNode_.idx, 0, nSeg - 1);
  auto [proj, last] = projectRun(first);

  // reference point passed the goal or end of the segment
  while (proj && proj->idx == last && proj->t >= 1.0f) {
    if (last + 1 >= nSeg) {
      RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000, "Goal reached: stopping.");
      return {0.0f, 0.0f};
    }
    first = last + 1;
    std::tie(proj, last) = projectRun(first);
  }

  closestNode_ = {{proj->x, proj->y, proj->heading}, proj->idx};
  const int dir = proj->dir;
  const Pose ref = trackedAxle(lastVehiclePose_->pose, dir);
  const float x_ref = ref.x;
  const float y_ref = ref.y;

  const float cte = (y_ref - proj->y) * std::cos(proj->tangent) -
    (x_ref - proj->x) * std::sin(proj->tangent);

  const float yaw_target = proj->tangent + (dir == -1 ? std::numbers::pi_v<float> : 0.0f);
  const float heading_error = wrapAngle(yaw_target - yaw);
  const float cte_error = std::atan2(-gain_cte * cte, soft_cte + maxSpeed);

  float phi = heading_error + cte_error;
  if (dir == -1) phi = -phi;
  phi = std::clamp(phi, -config_vehicle_max_steering, config_vehicle_max_steering);

  const float delta_phi = std::abs(phi - steeringAngleAct_);
  const float ratio = std::clamp((delta_phi - phiTol) / (phiErrMax - phiTol), 0.0f, 1.0f);
  const float speed = dir * std::max(maxSpeed * (1.0f - ratio), 0.001f);

  const float yaw_rate = (speed / config_vehicle_wheelbase) * std::tan(phi);

  if (debug_) {
    debugMsg_.yaw_rate = yaw_rate;
    debugMsg_.yaw = yaw;
    debugMsg_.cn_yaw = phi;
    debugMsg_.speed = speed;
    debugMsg_.steering_angle = steeringAngleAct_;
    debugMsg_.idx_closest_node = closestNode_.idx;
    debugMsg_.cte = cte;
    debugMsg_.heading_error = delta_phi;
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