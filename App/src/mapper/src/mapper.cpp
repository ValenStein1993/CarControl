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
  : Node("mapper") {
    config_ = common::get_config();

    // init ocup map
    occgrid_.resize(config_["occgrid"]["width"].as<int>() * config_["occgrid"]["height"].as<int>());
    // populate occup map with init values
    init_logOdd_ = std::log10(init_probOcc / (1 - init_probOcc));
    std::fill(std::begin(occgrid_), std::end(occgrid_), init_logOdd_);

    timer_ = this->create_wall_timer(100ms, std::bind(&Mapper::callback_map, this));
    pub_occGrid_ = create_publisher<nav_msgs::msg::OccupancyGrid>(
		config_["topics"]["occupancyGrid"].as<std::string>(), 10);

    sub_vehicleState_ = create_subscription<car_msgs::msg::VehicleState>(
        config_["topics"]["vehicleStateEkf"].as<std::string>(), 10, std::bind(&Mapper::callback_vehicleState, this, _1));
    sub_laserScan_ = create_subscription<sensor_msgs::msg::LaserScan>(
        config_["topics"]["laserScan"].as<std::string>(), 10, std::bind(&Mapper::callback_laserscan, this, _1));
}


void Mapper::callback_laserscan(const sensor_msgs::msg::LaserScan::SharedPtr msg) {
    if (!lastVehicleState_) {
        return;
    }

    for (size_t i = 0; i < msg->ranges.size(); ++i) {
        float rmax = msg->ranges[i];

        if (!std::isfinite(rmax))
            continue;

        if (rmax < msg->range_min || rmax > msg->range_max)
            continue;

        float theta_lidar = msg->angle_min + static_cast<float>(i) * msg->angle_increment;
        float theta_map = lastVehicleState_->yaw + theta_lidar;
        float xmax = rmax * std::cos(theta_map);
        float ymax = rmax * std::sin(theta_map);

        float res_occgrid = config_["occgrid"]["resolution"].as<float>();
        float x = lastVehicleState_->pos_x;
        float y = lastVehicleState_->pos_y;
        float r = 0;
        
        float stddev_lidar = config_["sensors"]["lidar"]["stddev"].as<float>();
        boost::math::normal_distribution lidar_dist{rmax, stddev_lidar};
        
        float x_inc, y_inc, r_inc;
        int sign_x, sign_y;
        if (std::abs(xmax - x) >= std::abs(ymax - y)) {
            x_inc = res_occgrid;
            r_inc = x_inc / std::cos(theta_map);
            y_inc = r_inc * std::sin(theta_map);
        }
        else {
            y_inc = res_occgrid;
            r_inc = y_inc / std::sin(theta_map);
            x_inc = r_inc * std::cos(theta_map);
        }

        if (x < 0) {
            sign_x = -1;
        }
        else {
            sign_x = 1;
        }

        if (y < 0) {
            sign_y = -1;
        }
        else {
            sign_y = 1;
        } 
        
        while (r <= rmax) {
            int idx_grid = Common::MapUtils::getMapIndexFromPos(x, y, config_);
            if (idx_grid == -1) {
                break;
            }

            float p = boost::math::pdf(lidar_dist, r);
            updateBinaryBayesFilter(idx_grid, p);

            x += sign_x * x_inc;
            y += sign_y * y_inc; 
            r += r_inc;
        }
    }
}


void Mapper::callback_vehicleState(const car_msgs::msg::VehicleState::SharedPtr msg) {
    lastVehicleState_ = msg;
}

void Mapper::callback_map() {
    nav_msgs::msg::OccupancyGrid occGridMsg;
    occGridMsg.header.stamp = this->get_clock()->now();
	occGridMsg.header.frame_id = config_["frames"]["odom"].as<std::string>();
    occGridMsg.info.height = config_["occgrid"]["height"].as<int>();
    occGridMsg.info.width = config_["occgrid"]["width"].as<int>();
    occGridMsg.info.resolution = config_["occgrid"]["resolution"].as<float>();
    occGridMsg.info.origin.position.x = -0.5 * config_["occgrid"]["width"].as<int>() * config_["occgrid"]["resolution"].as<float>();
    occGridMsg.info.origin.position.y = -0.5 * config_["occgrid"]["height"].as<int>() * config_["occgrid"]["resolution"].as<float>();
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