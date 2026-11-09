#pragma once
#include <vector>
#include <utility>
#include <optional>
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


constexpr float maxSpeed = 0.03;
constexpr float maxSpeedDist = 0.3;
constexpr float minDist = 0.1;
constexpr float gain_cte = 2.0;
// Stanley softening constant [m/s]: limits the cross-track term at low speed
constexpr float soft_cte = 0.1;


// projection of a point onto the planned path
struct PathProjection {
  float x, y;     // projected point on the path
  float tangent;  // direction of travel along the segment
  float heading;  // planned vehicle heading, interpolated along the segment
  float t;        // position on the segment [0, 1]
  int idx;        // index of the segment start pose
  int dir;        // +1 forward, -1 reverse
};

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

    int getDrivingDir(int i) const;
    bool isDegenerate(int i) const;
    int getSegmentEnd(int first) const;
    std::optional<PathProjection> projectOnPath(float pos_x, float pos_y, int first, int last) const;
    std::pair<float, float> calcSteering();

};