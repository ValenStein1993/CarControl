#pragma once

#include <gz/sim/System.hh>
#include <gz/sim/EntityComponentManager.hh>
#include <gz/msgs/imu.pb.h>
#include <gz/msgs/twist.pb.h>
#include <gz/transport/Node.hh>
#include <thread>
#include <rclcpp/executors/single_threaded_executor.hpp>

#include <rclcpp/rclcpp.hpp>

#include "car_msgs/msg/sensor_measurements.hpp"
#include "car_msgs/msg/steering.hpp"


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

    void OnImu(const gz::msgs::IMU &_msg);
    void OnSteering(const car_msgs::msg::Steering &_msg);

    
    rclcpp::executors::SingleThreadedExecutor::SharedPtr executor_;
    std::thread ros_spin_thread_;
    gz::transport::Node gz_node_;
    gz::transport::Node::Publisher gz_pub_steering_;

    rclcpp::Node::SharedPtr ros_node_;
    rclcpp::Publisher<car_msgs::msg::SensorMeasurements>::SharedPtr ros_pub_measurements_;
    rclcpp::Subscription<car_msgs::msg::Steering>::SharedPtr ros_sub_steering_;

    gz::msgs::IMU lastImu_;
    car_msgs::msg::Steering lastSteering_;
};
