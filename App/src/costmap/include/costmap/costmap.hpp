/*
 * costmpap.hpp
 *
 *  Created on: 20.10.2026
 *      Author: valen
 */

#pragma once
#include <cmath>
#include <opencv2/core/mat.hpp>

#include "rclcpp/rclcpp.hpp"
#include <nav_msgs/msg/occupancy_grid.hpp>
#include "common/config.hpp"
#include "common/basenode.hpp"

constexpr uint8_t cost_free = 0;
constexpr uint8_t cost_inscribed = 98;
constexpr uint8_t cost_lethal = 100;
constexpr uint8_t cost_unknown = -1;

constexpr int8_t p_occupied = 65;
constexpr int8_t cost_edge = 10;

const float radius_inscribed = 0.5 * config_vehicle_wheeltrack;
const float radius_inflation = 5 * radius_inscribed;
const float scale_cost = std::log(cost_inscribed / cost_edge) / (radius_inflation - radius_inscribed);


class CostMap : public BaseNode {
  public:
    CostMap();

  private:
    nav_msgs::msg::OccupancyGrid::SharedPtr lastOccGrid_;

  	rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr pub_costMap_;
    rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr sub_occGrid_;

    void callback_occGrid(const nav_msgs::msg::OccupancyGrid::SharedPtr msg);
    cv::Mat occgridToCostmap(const nav_msgs::msg::OccupancyGrid::SharedPtr msg);


};
