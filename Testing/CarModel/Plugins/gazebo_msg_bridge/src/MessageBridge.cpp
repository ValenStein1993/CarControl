#include <cmath>
#include <thread>
#include <mutex>
#include <yaml-cpp/yaml.h>

#include "gazebo_msg_bridge/MessageBridge.hpp"
#include <gz/plugin/Register.hh>
#include <gz/math/Quaternion.hh>

#include "common/config.hpp"
#include "car_msgs/msg/sensor_measurements.hpp"
#include "car_msgs/msg/motion_control.hpp"
#include "car_msgs/msg/vehicle_state.hpp"
#include <sensor_msgs/msg/laser_scan.hpp>



MessageBridge::MessageBridge() {
    config_ = common::get_config();
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

    ros_node_ = std::make_shared<rclcpp::Node>("sensor_measurements_bridge");
    executor_ = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
    executor_->add_node(ros_node_); 
    ros_spin_thread_ = std::thread([this]() { executor_->spin(); });

    // use gazebo node to subscribe to the sensor topics and then publish 
    // the data to custom message type using ros2 node
    gz_node_.Subscribe("/imu_sensor", &MessageBridge::callback_imu, this);
    gz_node_.Subscribe("/wheel_states", &MessageBridge::callback_jointState, this);

    ros_pub_measurements_ = ros_node_->create_publisher<car_msgs::msg::SensorMeasurements>(
        config_["topics"]["sensorMeasurements"].as<std::string>(),
        10
    );

    // subscribe to ROS motion control topic and publish via gazebo node
    ros_sub_motionControl_ = ros_node_->create_subscription<car_msgs::msg::MotionControl>(
        config_["topics"]["motionControl"].as<std::string>(),
        10,
        std::bind(&MessageBridge::callback_motionControl, this, std::placeholders::_1)
    );

    gz_pub_motionControl_ = gz_node_.Advertise<gz::msgs::Twist>("/cmd_vel");

    // subscribe to odometry data and publish true vehicle state via ROS node
    gz_node_.Subscribe("/model/CarModel/odometry", &MessageBridge::callback_odometry, this);
    ros_pub_vehicleState_ = ros_node_->create_publisher<car_msgs::msg::VehicleState>(
        config_["topics"]["vehicleStateAct"].as<std::string>(),
        10
    );

    // publish sensor calibration message
    ros_pub_calibration_ = ros_node_->create_publisher<car_msgs::msg::SensorCalibration>(
        config_["topics"]["sensorCalibration"].as<std::string>(),
        10
    );

    // publish laser scan data from LiDAR to ROS
    gz_node_.Subscribe("/lidar_sensor", &MessageBridge::callback_laserScan, this);
    ros_pub_laserScan_ = ros_node_->create_publisher<sensor_msgs::msg::LaserScan>(
        config_["topics"]["laserScan"].as<std::string>(),
        10
    );
}

void MessageBridge::callback_imu(const gz::msgs::IMU &_msg) {
    lastImu_ = _msg;
}

void MessageBridge::callback_laserScan(const gz::msgs::LaserScan &_msg) {
    std::lock_guard<std::mutex> lock(laserScanMutex_);
    lastLaserScan_ = _msg;
}

void MessageBridge::callback_motionControl(const car_msgs::msg::MotionControl &_msg) {
    lastMotionControl_ = _msg;
}

void MessageBridge::callback_odometry(const gz::msgs::Odometry &_msg) {
    lastOdometry_ = _msg;
}

void MessageBridge::callback_jointState(const gz::msgs::Model &_msg) {
    std::lock_guard<std::mutex> lock(jointStateMutex_);
    lastJointState_ = _msg;
}

void MessageBridge::PreUpdate(
    const gz::sim::UpdateInfo &_info,
    gz::sim::EntityComponentManager &_ecm) {

    gz::msgs::Twist msg;
    msg.mutable_linear()->set_x(lastMotionControl_.speed); 
    msg.mutable_angular()->set_z(lastMotionControl_.yaw_rate);

    gz_pub_motionControl_.Publish(msg);

}

void MessageBridge::PostUpdate(
    const gz::sim::UpdateInfo &_info,
    const gz::sim::EntityComponentManager &_ecm) {
    
    // publish measurements every 100ms
    if (_info.simTime - lastPublishTime_ < std::chrono::milliseconds(100)) {
        return;
    }
    lastPublishTime_ = _info.simTime;

    rclcpp::Time timestamp(
        std::chrono::duration_cast<std::chrono::nanoseconds>(
        _info.simTime).count());

    // Sensor Measurements Message
    car_msgs::msg::SensorMeasurements msgMeasurements;
    
    msgMeasurements.header.stamp = timestamp;
    msgMeasurements.mpu6050_accel_x = lastImu_.linear_acceleration().x();
    msgMeasurements.mpu6050_accel_y = lastImu_.linear_acceleration().y();
    msgMeasurements.mpu6050_accel_z = lastImu_.linear_acceleration().z();
    msgMeasurements.mpu6050_gyro_x = lastImu_.angular_velocity().x();
    msgMeasurements.mpu6050_gyro_y = lastImu_.angular_velocity().y();
    msgMeasurements.mpu6050_gyro_z = lastImu_.angular_velocity().z();
    
    // make local copy of joint state while mutex is locked
    gz::msgs::Model jointState;
    {
        std::lock_guard<std::mutex> lock(jointStateMutex_);
        jointState = lastJointState_;
    }

    for (const auto &joint : jointState.joint()) {

        if (joint.name() == "left_backwheel_joint") {
            leftWheelSpeed_ = joint.axis1().velocity();
        }
        else if (joint.name() == "right_backwheel_joint") {
            rightWheelSpeed_ = joint.axis1().velocity();
        }
        else if (joint.name() == "left_steering_joint") {
            leftSteeringSpeed_ = joint.axis1().velocity();
            leftSteeringPosition_ = joint.axis1().position();
        }
        else if (joint.name() == "right_steering_joint") {
            rightSteeringSpeed_ = joint.axis1().velocity();
            rightSteeringPosition_ = joint.axis1().position();
        }
    }

    float rotSpeed = 0.5 * (leftWheelSpeed_ + rightWheelSpeed_);
    float rotPositionSteering = 0.5 * (leftSteeringPosition_ + rightSteeringPosition_);
    float rotSpeedSteering = 0.5 * (leftSteeringSpeed_ + rightSteeringSpeed_);
    
    msgMeasurements.wheelencoder_rotspeed = rotSpeed;
    msgMeasurements.wheelencoder_translspeed = rotSpeed * config_["vehicle"]["wheels"]["radius"].as<float>();
    msgMeasurements.cjmcu103_angle = rotPositionSteering;
    msgMeasurements.cjmcu103_anglespeed = rotSpeedSteering;

    ros_pub_measurements_->publish(msgMeasurements);

    // Sensor Calibration Message
    car_msgs::msg::SensorCalibration calibrationMsg;
    calibrationMsg.is_calibrated = true;
    calibrationMsg.mpu6050_var_accel_x = 4e-4f;
    calibrationMsg.mpu6050_var_gyro_z = 1e-4f;
    calibrationMsg.wheelencoder_var_rotspeed = 1e-8f;
    calibrationMsg.cjmcu103_var_angle = 1e-8f;


    ros_pub_calibration_->publish(calibrationMsg);

    // Actual Vehicle State Message
    car_msgs::msg::VehicleState msgState;
    msgState.header.stamp = timestamp;
    msgState.pos_x = lastOdometry_.pose().position().x();
    msgState.pos_y = lastOdometry_.pose().position().y();
    msgState.speed = lastOdometry_.twist().linear().x();

    const auto &orientation = lastOdometry_.pose().orientation();
    gz::math::Quaterniond q(
        orientation.w(),
        orientation.x(),
        orientation.y(),
        orientation.z()
    );
    msgState.yaw = q.Yaw();

    ros_pub_vehicleState_->publish(msgState);

    // Laser Scan Message
    sensor_msgs::msg::LaserScan msgLaserScan;

    gz::msgs::LaserScan lastLaserScan;
    {
        std::lock_guard<std::mutex> lock(laserScanMutex_);
        lastLaserScan = lastLaserScan_;
    }

    msgLaserScan.header.stamp = timestamp;
    msgLaserScan.header.frame_id = "lidar";
    msgLaserScan.angle_min = lastLaserScan.angle_min();
    msgLaserScan.angle_max = lastLaserScan.angle_max();
    msgLaserScan.angle_increment = lastLaserScan.angle_step();
    msgLaserScan.range_min = lastLaserScan.range_min();
    msgLaserScan.range_max = lastLaserScan.range_max();
    msgLaserScan.ranges.resize(lastLaserScan.ranges_size());

    for (int i = 0; i < lastLaserScan.ranges_size(); ++i) {
        msgLaserScan.ranges[i] = lastLaserScan.ranges(i);
    }

    msgLaserScan.intensities.resize(lastLaserScan.intensities_size());

    for (int i = 0; i < lastLaserScan.intensities_size(); ++i) {
        msgLaserScan.intensities[i] = lastLaserScan.intensities(i);
    }

    ros_pub_laserScan_->publish(msgLaserScan);

}

GZ_ADD_PLUGIN(
    MessageBridge,
    gz::sim::System,
    gz::sim::ISystemConfigure,
    gz::sim::ISystemPreUpdate,
    gz::sim::ISystemPostUpdate
)
