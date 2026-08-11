#include "gazebo_msg_bridge/MessageBridge.hpp"
#include <gz/plugin/Register.hh>
#include "car_msgs/msg/sensor_measurements.hpp"
#include "car_msgs/msg/steering.hpp"
#include <thread>


MessageBridge::MessageBridge() {
}


MessageBridge::~MessageBridge() {
    if (executor_) {
        executor_->cancel();
    }

    if (ros_spin_thread_.joinable()) {
        ros_spin_thread_.join();
    }
}


void MessageBridge::Configure(
    const gz::sim::Entity &_entity,
    const std::shared_ptr<const sdf::Element> &_sdf,
    gz::sim::EntityComponentManager &_ecm,
    gz::sim::EventManager &_eventMgr) {

    if (!rclcpp::ok()) {
        rclcpp::init(0, nullptr);
    }

    // use gazebo node to subscribe to the sensor topics and then publish 
    // the data to custom message type using ros2 node
    gz_node_.Subscribe("/imu", &MessageBridge::OnImu, this);

    ros_node_ = std::make_shared<rclcpp::Node>("sensor_measurements_bridge");

    executor_ = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
    executor_->add_node(ros_node_);
    ros_spin_thread_ = std::thread([this]() { executor_->spin(); });

    ros_pub_measurements_ = ros_node_->create_publisher<car_msgs::msg::SensorMeasurements>(
        "/sensor_measurements",
        10
    );

    // subscribe to ROS steering topic and publish via gazebo node
    ros_sub_steering_ = ros_node_->create_subscription<car_msgs::msg::Steering>(
        "/steering",
        10,
        std::bind(&MessageBridge::OnSteering, this, std::placeholders::_1)
    );

    gz_pub_steering_ = gz_node_.Advertise<gz::msgs::Twist>("/cmd_vel");
}

void MessageBridge::OnImu(const gz::msgs::IMU &_msg) {
    lastImu_ = _msg;
}

void MessageBridge::OnSteering(const car_msgs::msg::Steering &_msg) {
    lastSteering_ = _msg;
}

void MessageBridge::PreUpdate(
    const gz::sim::UpdateInfo &_info,
    gz::sim::EntityComponentManager &_ecm) {

    gz::msgs::Twist msg;
    msg.mutable_linear()->set_x(lastSteering_.speed); 
    msg.mutable_angular()->set_z(lastSteering_.steering_angle);

    gz_pub_steering_.Publish(msg);

}

void MessageBridge::PostUpdate(
    const gz::sim::UpdateInfo &_info,
    const gz::sim::EntityComponentManager &_ecm) {

    if (!ros_pub_measurements_)
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

    ros_pub_measurements_->publish(msg);
}

GZ_ADD_PLUGIN(
    MessageBridge,
    gz::sim::System,
    gz::sim::ISystemConfigure,
    gz::sim::ISystemPreUpdate,
    gz::sim::ISystemPostUpdate
)
