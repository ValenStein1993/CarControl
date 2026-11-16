#pragma once
#include "rclcpp/rclcpp.hpp"

#include "common/config.hpp"
#include <cmath>
#include <utility>
#include <nav_msgs/msg/map_meta_data.hpp>
#include <tf2_ros/buffer.h>
#include <optional>
#include <tf2/LinearMath/Transform.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>



namespace Common::MapUtils
{
    inline int getMapIndexFromPos(float x, float y, const nav_msgs::msg::MapMetaData* mapMetaData) {
        const auto x_min = mapMetaData->origin.position.x;
        const auto y_min = mapMetaData->origin.position.y;
        const auto x_max = x_min + mapMetaData->width * mapMetaData->resolution;
        const auto y_max = y_min + mapMetaData->height * mapMetaData->resolution;

        if ((x < x_min) | (y < y_min) | (x > x_max) | (y > y_max))
            return -1;

        const int grid_x = static_cast<int>(std::floor((x - x_min) / mapMetaData->resolution));
        const int grid_y = static_cast<int>(std::floor((y - y_min) / mapMetaData->resolution));

        return grid_x + grid_y * mapMetaData->width;
    }

    inline std::pair<float, float> getPosFromMapIndex(int idx, const nav_msgs::msg::MapMetaData* mapMetaData) {
        const auto width = mapMetaData->width;
        const auto resolution = mapMetaData->resolution;

        const auto x = idx % width;
        const auto y = idx / width;

        const float posX = x * resolution + mapMetaData->origin.position.x;
        const float posY = y * resolution + mapMetaData->origin.position.y;

        return {posX, posY};
    }

    inline bool checkGridBoundries(float x, float y, const nav_msgs::msg::MapMetaData* mapMetaData) {
        const auto width = mapMetaData->width;

        const auto idx = getMapIndexFromPos(x, y, mapMetaData);
        const auto vx = idx % width;
        const auto vy = idx / width;

        if (vx < 0 || vy < 0 || vx >= mapMetaData->width || vy >= mapMetaData->height) return false;
        return true;
    }

}


namespace Common::MathUtils
{
    // wraps an angle [rad] to [-pi, pi]
    inline float wrapAngle(float a) {
        return std::atan2(std::sin(a), std::cos(a));
    }

}

namespace Common::TfUtils
{
    inline std::optional<tf2::Transform> lookupRearAxleToBaseTransform(std::unique_ptr<tf2_ros::Buffer>& buffer) {
        const std::string chassis{config_frames_vehicle_chassis};
        const std::string rearAxle{config_frames_vehicle_rear_axle};

        if (!buffer->canTransform(rearAxle, chassis, tf2::TimePointZero)) {
            return std::nullopt;
        }

        tf2::Transform rear_to_chassis;
        const auto t = buffer->lookupTransform(rearAxle, chassis, tf2::TimePointZero);
        tf2::fromMsg(t.transform, rear_to_chassis);

        return rear_to_chassis;
    }

    inline std::optional<tf2::Transform> lookupBaseToRearAxleTransform(std::unique_ptr<tf2_ros::Buffer>& buffer) {
        const std::string chassis{config_frames_vehicle_chassis};
        const std::string rearAxle{config_frames_vehicle_rear_axle};

        if (!buffer->canTransform(chassis, rearAxle, tf2::TimePointZero)) {
            return std::nullopt;
        }

        tf2::Transform chassis_to_rear_axle;
        const auto t = buffer->lookupTransform(chassis, rearAxle, tf2::TimePointZero);
        tf2::fromMsg(t.transform, chassis_to_rear_axle);

        return chassis_to_rear_axle;
    }
}
