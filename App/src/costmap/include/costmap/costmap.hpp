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
constexpr int8_t scale_cost = 3;
constexpr int8_t radius_inflation = 0.2;

const float radius_vehTurn = config_vehicle_wheelbase / std::tan(config_vehicle_max_steering);


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
