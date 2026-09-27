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
    // init ocup map
    occgrid_.resize(config_occgrid_width * config_occgrid_height);

    // populate occup map with init values
    init_logOdd_ = std::log(init_probOcc / (1 - init_probOcc));
    std::fill(std::begin(occgrid_), std::end(occgrid_), init_logOdd_);

    add_timer(100ms, &Mapper::publish_map);

    pub_occGrid_ = create_publisher<nav_msgs::msg::OccupancyGrid>(
        static_cast<std::string>(config_topics_occupancyGrid), 10);

    sub_vehicleState_ = create_subscription<car_msgs::msg::VehicleState>(
        static_cast<std::string>(config_topics_vehicleStateEkf), 10, 
        std::bind(&Mapper::callback_vehicleState, this, _1));
    sub_laserScan_ = create_subscription<sensor_msgs::msg::LaserScan>(
        static_cast<std::string>(config_topics_laserScan), 10, 
        std::bind(&Mapper::callback_laserscan, this, _1));
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
        float step = 0.5 * config_occgrid_resolution;

        float x = lastVehicleState_->pos_x;
        float y = lastVehicleState_->pos_y;

        int idx_hit = -1;
        if (hit) {
            idx_hit = Common::MapUtils::getMapIndexFromPos(
                lastVehicleState_->pos_x + dx*rmax, lastVehicleState_->pos_y + dy*rmax);
        }

        int last_idx = -1;
        for (float r = 0.f; r < rmax; r += step, x += dx*step, y += dy*step) {
            int idx = Common::MapUtils::getMapIndexFromPos(x, y);
            if (idx < 0) break;

            // continue if idx is hit cell or last cell
            if (idx == last_idx || idx == idx_hit) continue;  
            // update binary bayes filter with free odd
            occgrid_[idx] = std::clamp(occgrid_[idx] + l_free - init_logOdd_, l_min, l_max);
            last_idx = idx;
        }
        if (hit && idx_hit >= 0) {
            // update binary bayes filter with occupied odd
            occgrid_[idx_hit] = std::clamp(occgrid_[idx_hit] + l_occ - init_logOdd_, l_min, l_max);
        }
    }
}


void Mapper::callback_vehicleState(const car_msgs::msg::VehicleState::SharedPtr msg) {
    lastVehicleState_ = msg;
}

void Mapper::publish_map() {
    nav_msgs::msg::OccupancyGrid occGridMsg;
    occGridMsg.header.stamp = this->get_clock()->now();
	occGridMsg.header.frame_id = config_frames_ekf_odom;
    occGridMsg.info.height = config_occgrid_height;
    occGridMsg.info.width = config_occgrid_width;
    occGridMsg.info.resolution = config_occgrid_resolution;
    occGridMsg.info.origin.position.x = -0.5 * config_occgrid_width * config_occgrid_resolution;
    occGridMsg.info.origin.position.y = -0.5 * config_occgrid_height * config_occgrid_resolution;
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


int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Mapper>());
    rclcpp::shutdown();
    return 0;
}