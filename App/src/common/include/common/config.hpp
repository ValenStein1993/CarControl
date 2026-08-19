#pragma once

#include <string>

#include <ament_index_cpp/get_package_share_directory.hpp>
#include <yaml-cpp/yaml.h>

namespace common
{

    inline std::string get_config_path() {
        return ament_index_cpp::get_package_share_directory("common")
            + "/config/config.yaml";
    }

    inline YAML::Node get_config() {
        return YAML::LoadFile(get_config_path());
    }

}