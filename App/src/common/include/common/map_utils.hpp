#pragma once
#include <yaml-cpp/yaml.h>


namespace Common::MapUtils
{
inline int getMapIndexFromPos(float x, float y, YAML::Node& config) {
    const int width = config["occgrid"]["width"].as<int>();
    const int height = config["occgrid"]["height"].as<int>();
    const float resolution = config["occgrid"]["resolution"].as<float>();

    const float x_min = -0.5f * width * resolution;
    const float y_min = -0.5f * height * resolution;

    if ((std::abs(x) > std::abs(x_min)) | (std::abs(y) > std::abs(y_min)))
        return -1;

    const int grid_x = static_cast<int>(std::floor((x - x_min) / resolution));
    const int grid_y = static_cast<int>(std::floor((y - y_min) / resolution));

    return grid_x + grid_y * width;
}

inline std::pair<float, float> getPosFromMapIndex(int idx, YAML::Node& config) {
    const int width = config["occgrid"]["width"].as<int>();
    const int height = config["occgrid"]["height"].as<int>();
    const float resolution = config["occgrid"]["resolution"].as<float>();

    const float x_min = -0.5f * width * resolution;
    const float y_min = -0.5f * height * resolution;

    int grid_x = idx % width;
    int grid_y = idx / width;

    float x = x_min + (grid_x + 0.5f) * resolution;
    float y = y_min + (grid_y + 0.5f) * resolution;

    return {x, y};
}
}