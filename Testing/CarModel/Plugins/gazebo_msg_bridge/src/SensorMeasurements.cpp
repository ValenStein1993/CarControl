#include "gazebo_msg_bridge/SensorMeasurements.hpp"
#include <gz/plugin/Register.hh>
#include "car_msgs/msg/sensor_measurements.hpp"

using namespace msg_bridge;


SensorMeasurements::SensorMeasurements() {
}


SensorMeasurements::~SensorMeasurements() {
}


void SensorMeasurements::Configure(
    const gz::sim::Entity &_entity,
    const std::shared_ptr<const sdf::Element> &_sdf,
    gz::sim::EntityComponentManager &_ecm,
    gz::sim::EventManager &_eventMgr) {

    // use gazebo node to subscribe to the sensor topics and then publish 
    // the data to custom message type using ros2 node

    if (!rclcpp::ok()) {
        rclcpp::init(0, nullptr);
    }


    ros_node_ = std::make_shared<rclcpp::Node>("sensor_measurements_bridge");

    publisher_ = ros_node_->create_publisher<car_msgs::msg::SensorMeasurements>(
        "/sensor_measurements",
        10
    );

    gz_node_.Subscribe("/imu", &SensorMeasurements::OnImu, this);


    RCLCPP_INFO(
        ros_node_->get_logger(),
        "SensorMeasurements bridge started"
    );
}

void SensorMeasurements::OnImu(const gz::msgs::IMU &_msg) {
    lastImu_ = _msg;
}



void SensorMeasurements::PostUpdate(
    const gz::sim::UpdateInfo &_info,
    const gz::sim::EntityComponentManager &_ecm) {

    if (!publisher_)
        return;

    car_msgs::msg::SensorMeasurements msg;

    msg.time = static_cast<uint32_t>(
            ros_node_->get_clock()->now().nanoseconds()
            / 1000000);    
    msg.mpu6050_accel_x = lastImu_.linear_acceleration().x();
    msg.mpu6050_accel_y = lastImu_.linear_acceleration().y();
    msg.mpu6050_accel_z = lastImu_.linear_acceleration().z();
    msg.mpu6050_gyro_x = lastImu_.angular_velocity().x();
    msg.mpu6050_gyro_y = lastImu_.angular_velocity().y();
    msg.mpu6050_gyro_z = lastImu_.angular_velocity().z();

    publisher_->publish(msg);
}


GZ_ADD_PLUGIN(
    SensorMeasurements,
    gz::sim::System,
    gz::sim::ISystemConfigure,
    gz::sim::ISystemPostUpdate
)