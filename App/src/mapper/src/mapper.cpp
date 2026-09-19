#include <chrono>
#include <numbers>
#include <cmath>
#include <random>

#include "mapper/mapper.hpp"
#include "car_msgs/msg/vehicle_state.hpp"
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include "common/config.hpp"
#include "common/map_utils.hpp"
#include <boost/math/distributions/normal.hpp> 


using namespace std::chrono_literals;
using std::placeholders::_1;


Mapper::Mapper()
  : BaseNode("mapper")
{
    config_occgrid_resolution_ = config_["occgrid"]["resolution"].as<float>();
    config_sensors_lidar_stddev_ = config_["sensors"]["lidar"]["stddev"].as<float>();
    config_frames_odom_ = config_["frames"]["odom"].as<std::string>();
    config_occgrid_width_ = config_["occgrid"]["width"].as<int>();
    config_occgrid_height_ = config_["occgrid"]["height"].as<int>();

    // init ocup map
    occgrid_.resize(config_occgrid_width_ * config_occgrid_height_);

    // populate occup map with init values
    init_logOdd_ = std::log10(init_probOcc / (1 - init_probOcc));
    std::fill(std::begin(occgrid_), std::end(occgrid_), init_logOdd_);

    add_timer(100ms, &Mapper::publish_map);

    pub_occGrid_ = create_publisher<nav_msgs::msg::OccupancyGrid>(
		config_["topics"]["occupancyGrid"].as<std::string>(), 10);

    sub_vehicleState_ = create_subscription<car_msgs::msg::VehicleState>(
        config_["topics"]["vehicleStateEkf"].as<std::string>(), 10, std::bind(&Mapper::callback_vehicleState, this, _1));
    sub_laserScan_ = create_subscription<sensor_msgs::msg::LaserScan>(
        config_["topics"]["laserScan"].as<std::string>(), 10, std::bind(&Mapper::callback_laserscan, this, _1));
}


void Mapper::callback_laserscan(const sensor_msgs::msg::LaserScan::SharedPtr msg) 
{
    if (!lastVehicleState_) {
        return;
    }

    float p_occ = 0.7f;
    float l_free = std::log((1 - p_occ) / p_occ);
    float l_occ = std::log(p_occ / (1 - p_occ));
    float l_min = -5.f;
    float l_max = 5.f;

    for (size_t i = 0; i < msg->ranges.size(); ++i) {
        float range = msg->ranges[i];

        if (!std::isfinite(range) || range < msg->range_min) continue;

        bool hit = range < msg->range_max;
        float rmax = std::min(range, msg->range_max);

        float theta = lastVehicleState_->yaw + msg->angle_min + i * msg->angle_increment;
        float dx = std::cos(theta);
        float dy = std::sin(theta);
        float step = 0.5f * config_occgrid_resolution_;

        float x = lastVehicleState_->pos_x;
        float y = lastVehicleState_->pos_y;

        int last_idx = -1;
        for (float r = 0.f; r < rmax; r += step, x += dx*step, y += dy*step) {
            int idx = Common::MapUtils::getMapIndexFromPos(x, y, config_occgrid_width_,
                config_occgrid_height_, config_occgrid_resolution_);
            if (idx < 0) break;
            if (idx == last_idx) continue;  // don't update the same cell twice
            occgrid_[idx] = std::clamp(occgrid_[idx] + l_free, l_min, l_max);
            last_idx = idx;
        }
        if (hit) {
            int idx = Common::MapUtils::getMapIndexFromPos(
                lastVehicleState_->pos_x + dx*rmax, lastVehicleState_->pos_y + dy*rmax,
                config_occgrid_width_, config_occgrid_height_, config_occgrid_resolution_);
            if (idx >= 0) occgrid_[idx] = std::clamp(occgrid_[idx] + l_occ, l_min, l_max);
        }
    }
}


void Mapper::callback_vehicleState(const car_msgs::msg::VehicleState::SharedPtr msg) {
    lastVehicleState_ = msg;
}

void Mapper::publish_map() {
    nav_msgs::msg::OccupancyGrid occGridMsg;
    occGridMsg.header.stamp = this->get_clock()->now();
	occGridMsg.header.frame_id = config_frames_odom_;
    occGridMsg.info.height = config_occgrid_height_;
    occGridMsg.info.width = config_occgrid_width_;
    occGridMsg.info.resolution = config_occgrid_resolution_;
    occGridMsg.info.origin.position.x = -0.5 * config_occgrid_width_ * config_occgrid_resolution_;
    occGridMsg.info.origin.position.y = -0.5 * config_occgrid_height_ * config_occgrid_resolution_;
    occGridMsg.info.origin.position.z = 0.0;
    occGridMsg.data.resize(occgrid_.size());

    for (size_t i = 0; i < occgrid_.size(); ++i) {
        float log_odds = occgrid_[i];

        // convert log-odds back to probability
        float p = 1.0f / (1.0f + std::exp(-log_odds));
        int8_t value = static_cast<int8_t>(p * 100.0f);
        occGridMsg.data[i] = value;
    }
    
    pub_occGrid_->publish(occGridMsg);
}

void Mapper::updateBinaryBayesFilter(int idx, float p) {
    float* l_prior = &occgrid_[idx];
    *l_prior = std::log10(p / (1 - p)) + *l_prior - init_logOdd_;
}

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Mapper>());
    rclcpp::shutdown();
    return 0;
}