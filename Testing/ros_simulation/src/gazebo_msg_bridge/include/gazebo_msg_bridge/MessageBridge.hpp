#pragma once

#include <gz/sim/System.hh>
#include <gz/sim/EntityComponentManager.hh>
#include <gz/msgs/imu.pb.h>
#include <gz/msgs/model.pb.h>
#include <gz/msgs/twist.pb.h>
#include <gz/transport/Node.hh>
#include "gz/msgs/odometry.pb.h"
#include <gz/msgs/laserscan.pb.h>

#include <thread>
#include <rclcpp/executors/single_threaded_executor.hpp>

#include <rclcpp/rclcpp.hpp>

#include "car_msgs/msg/sensor_measurements.hpp"
#include "car_msgs/msg/sensor_calibration.hpp"
#include "car_msgs/msg/motion_control.hpp"
#include "car_msgs/msg/vehicle_state.hpp"
#include <sensor_msgs/msg/laser_scan.hpp>

class MessageBridge:
    public gz::sim::System,
    public gz::sim::ISystemConfigure,
    public gz::sim::ISystemPreUpdate,
    public gz::sim::ISystemPostUpdate
{

public:

    MessageBridge();

    ~MessageBridge() override;


    void Configure(
        const gz::sim::Entity &_entity,
        const std::shared_ptr<const sdf::Element> &_sdf,
        gz::sim::EntityComponentManager &_ecm,
        gz::sim::EventManager &_eventMgr
    ) override;


    void PostUpdate(
        const gz::sim::UpdateInfo &_info,
        const gz::sim::EntityComponentManager &_ecm
    ) override;

    void PreUpdate(
        const gz::sim::UpdateInfo &_info,
        gz::sim::EntityComponentManager &_ecm
    ) override;


private:
    gz::sim::Entity modelEntity_;

    void callback_imu(const gz::msgs::IMU &_msg);
    void callback_motionControl(const car_msgs::msg::MotionControl &_msg);
    void callback_jointState(const gz::msgs::Model &_msg);
    void callback_laserScan(const gz::msgs::LaserScan &_msg);

    std::chrono::steady_clock::duration lastPublishTime_{0};

    rclcpp::executors::SingleThreadedExecutor::SharedPtr executor_;
    std::thread ros_spin_thread_;
    gz::transport::Node gz_node_;
    gz::transport::Node::Publisher gz_pub_motionControl_;

    rclcpp::Node::SharedPtr ros_node_;
    rclcpp::Subscription<car_msgs::msg::MotionControl>::SharedPtr ros_sub_motionControl_;
    rclcpp::Publisher<car_msgs::msg::SensorMeasurements>::SharedPtr ros_pub_measurements_;
    rclcpp::Publisher<car_msgs::msg::SensorCalibration>::SharedPtr ros_pub_calibration_;
    rclcpp::Publisher<car_msgs::msg::VehicleState>::SharedPtr ros_pub_vehicleState_;
    rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr ros_pub_laserScan_;


    gz::msgs::IMU lastImu_;
    gz::msgs::Model lastJointState_;
    std::mutex jointStateMutex_;
    car_msgs::msg::MotionControl lastMotionControl_;
    gz::msgs::LaserScan lastLaserScan_;
    std::mutex laserScanMutex_;


    float leftWheelSpeed_{0};
    float rightWheelSpeed_{0};
    float leftSteeringSpeed_{0};
    float rightSteeringSpeed_{0};
    float leftSteeringPosition_{0};
    float rightSteeringPosition_{0};
};
