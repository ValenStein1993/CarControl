#pragma once
#include "common/config.hpp"
#include <cmath>
#include <nav_msgs/msg/map_meta_data.hpp>


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