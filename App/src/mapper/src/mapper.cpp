#include <chrono>

#include "mapper.hpp"
#include "car_msgs/msg/vehicle_state.hpp"
#include <sensor_msgs/msg/laser_scan.hpp>
#include "common/config.hpp"



using namespace std::chrono_literals;
using std::placeholders::_1;


Mapper::Mapper()
  : Node("mapper") {
    config_ = common::get_config();

    // init ocup map
    occgrid_.resize(config_["occgrid"]["width"].as<int>() * config_["occgrid"]["height"].as<int>());
    // populate occup map with init values
    std::fill(std::begin(occgrid_), std::end(occgrid_), init_probOcc);

    timer_ = this->create_wall_timer(100ms, std::bind(&Mapper::callback_map, this));

    sub_vehicleState_ = create_subscription<car_msgs::msg::VehicleState>(
        config_["topics"]["vehicleState"].as<std::string>(), 10, std::bind(&Mapper::callback_vehicleState, this, _1));
    sub_laserScan_ = create_subscription<sensor_msgs::msg::LaserScan>(
        config_["topics"]["laserScan"].as<std::string>(), 10, std::bind(&Mapper::callback_laserscan, this, _1));
}


void Mapper::callback_laserscan(const sensor_msgs::msg::LaserScan::SharedPtr msg) {
    for (size_t i = 0; i < msg->ranges.size(); ++i)
    {
        float r = msg->ranges[i];

        if (!std::isfinite(r))
            continue;

        if (r < msg->range_min || r > msg->range_max)
            continue;

        float theta = msg->angle_min + static_cast<float>(i) * msg->angle_increment;
        float x = r * std::cos(theta);
        float y = r * std::sin(theta);

        // Process (x, y) ...
    }
}
}

void Mapper::callback_vehicleState(const car_msgs::msg::VehicleState::SharedPtr msg) {
    lastVehicleState_ = msg;
}

void Mapper::callback_map() {
    // publish 2d odometry map message
}

