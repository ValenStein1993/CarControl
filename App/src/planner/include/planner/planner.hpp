#pragma once
#include <vector>
#include <utility>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>

#include "rclcpp/rclcpp.hpp"
#include "car_msgs/msg/vehicle_state.hpp"
#include "car_msgs/msg/motion_control.hpp"
#include "car_msgs/msg/node_state.hpp"
#include "car_msgs/msg/debug_planner.hpp"
#include "car_msgs/msg/path_node.hpp"

#include "common/basenode.hpp"
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <nav_msgs/msg/path.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav_msgs/msg/map_meta_data.hpp>
#include "common/datatypes.hpp"


constexpr float maxSpeed = 0.02;
constexpr float gain_cte = 0.5;
constexpr int n_binsAngle = 36;
constexpr float latticeRes = 0.05f;


class Planner : public BaseNode {
  public:
    Planner();
	
  private:

    std::pair<float, float> target_{};
    Pose targetNode_;
    std::vector<Pose> path_; 
    float distAhead_;
    GridNode updateNode_;
    bool mapReady_;


    geometry_msgs::msg::PoseStamped::SharedPtr lastVehiclePose_;
    sensor_msgs::msg::LaserScan::SharedPtr lastLaserScan_;
    nav_msgs::msg::OccupancyGrid::SharedPtr lastOccGrid_;
    nav_msgs::msg::MapMetaData* gridMetaData_;

    std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
    std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

  	rclcpp::Publisher<car_msgs::msg::MotionControl>::SharedPtr pub_motionControl_;
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pub_path_;
	
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr sub_vehiclePose_;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr sub_laserScan_;
    rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr sub_occGrid_;
    rclcpp::Subscription<car_msgs::msg::PathNode>::SharedPtr sub_closestNode_;


    void callback_vehiclePose(const geometry_msgs::msg::PoseStamped::SharedPtr msg);
    void callback_laserScan(const sensor_msgs::msg::LaserScan::SharedPtr msg);
    void callback_occGrid(const nav_msgs::msg::OccupancyGrid::SharedPtr msg);
    void callback_closestNode(const car_msgs::msg::PathNode::SharedPtr msg);

    void publish_path();

    std::vector<Pose> findShortestPath(GridNode startNode);
    void setTargetNode();
    void setUpdateNode();
    bool checkMapReady();
    float moveVehicle(Pose& start, float s, float phi, Pose& end, float& avgCost);

};