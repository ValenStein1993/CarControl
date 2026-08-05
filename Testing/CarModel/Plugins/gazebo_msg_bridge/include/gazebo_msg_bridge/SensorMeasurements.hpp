#pragma once

#include <gz/sim/System.hh>
#include <gz/sim/EntityComponentManager.hh>
#include <gz/msgs/imu.pb.h>
#include <gz/transport/Node.hh>

#include <rclcpp/rclcpp.hpp>

#include "car_msgs/msg/sensor_measurements.hpp"


namespace msg_bridge
{

class SensorMeasurements :
    public gz::sim::System,
    public gz::sim::ISystemConfigure,
    public gz::sim::ISystemPostUpdate
{

public:

    SensorMeasurements();

    ~SensorMeasurements() override;


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


private:

    void OnImu(const gz::msgs::IMU &_msg);


    gz::transport::Node gz_node_;

    rclcpp::Node::SharedPtr ros_node_;
    rclcpp::Publisher<car_msgs::msg::SensorMeasurements>::SharedPtr publisher_;

    gz::msgs::IMU lastImu_;

};

}