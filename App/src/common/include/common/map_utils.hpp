#pragma once
#include "common/config.hpp"
#include <cmath>

namespace Common::MapUtils
{
    inline int getMapIndexFromPos(float x, float y) {
        const float x_min = -0.5f * config_occgrid_width * config_occgrid_resolution;
        const float y_min = -0.5f * config_occgrid_height * config_occgrid_resolution;

        if ((std::abs(x) > std::abs(x_min)) | (std::abs(y) > std::abs(y_min)))
            return -1;

        const int grid_x = static_cast<int>(std::floor((x - x_min) / config_occgrid_resolution));
        const int grid_y = static_cast<int>(std::floor((y - y_min) / config_occgrid_resolution));

        return grid_x + grid_y * config_occgrid_width;
    }

    inline std::pair<float, float> getPosFromMapIndex(int idx) {
        const float x_min = -0.5f * config_occgrid_width * config_occgrid_resolution;
        const float y_min = -0.5f * config_occgrid_height * config_occgrid_resolution;

        int grid_x = idx % config_occgrid_width;
        int grid_y = idx / config_occgrid_width;

        float x = x_min + (grid_x + 0.5f) * config_occgrid_resolution;
        float y = y_min + (grid_y + 0.5f) * config_occgrid_resolution;

        return {x, y};
    }

    inline bool checkGridBoundries(int vx, int vy) {
        if (vx < 0 || vy < 0 || vx >= config_occgrid_width || vy >= config_occgrid_height) return false;
        return true;
    }

}