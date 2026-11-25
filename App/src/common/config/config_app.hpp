/*
 * config_app.hpp
 *
 *  Created on: 26.10.2026
 *      Author: valen
 */

#pragma once
#include <array>
#include <cmath>
#include <cstdint>
#include "common/config.hpp"

namespace Config::Costmap {
    constexpr uint8_t cost_free = 0;
    constexpr uint8_t cost_inscribed = 98;
    constexpr uint8_t cost_lethal = 100;
    constexpr uint8_t cost_unknown = 50;
    constexpr uint8_t cost_update = 50;
}

namespace Config::Vehicle {
    constexpr float width = config_vehicle_wheeltrack + config_vehicle_wheels_width;
    constexpr float length = config_vehicle_chassis_main_length + config_vehicle_chassis_front_length;
}

namespace Config::Footprint {
    constexpr int n_circles = 3;
    constexpr float spacing = Config::Vehicle::length / n_circles;
    const float radius = std::sqrt(0.25f * spacing * spacing + 0.25f * Config::Vehicle::width * Config::Vehicle::width)
                                + 0.5f * config_occgrid_resolution;
}

namespace Config::Planner {
    constexpr float maxSteering = 0.9f * config_vehicle_max_steering;
}
