#include <chrono>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

#include "costmap/costmap.hpp"
#include "rclcpp/rclcpp.hpp"
#include "common/config.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

CostMap::CostMap()
  : BaseNode("costmap") {

  pub_costMap_ = create_publisher<nav_msgs::msg::OccupancyGrid>(
    static_cast<std::string>(config_topics_costMap), 10);

  sub_occGrid_ = create_subscription<nav_msgs::msg::OccupancyGrid>(
    static_cast<std::string>(config_topics_occupancyGrid), 10, 
    std::bind(&CostMap::callback_occGrid, this, _1));
}

void CostMap::callback_occGrid(const nav_msgs::msg::OccupancyGrid::SharedPtr msg) {

  if (msg->info.width == 0 || msg->info.height == 0) {
    return;
  }

  cv::Mat costmap = occgridToCostmap(msg);

  nav_msgs::msg::OccupancyGrid costMapMsg;
  costMapMsg.header = msg->header;
  costMapMsg.info = msg->info;
  costMapMsg.data.assign(costmap.begin<int8_t>(), costmap.end<int8_t>());
  pub_costMap_->publish(costMapMsg);
}

cv::Mat CostMap::occgridToCostmap(const nav_msgs::msg::OccupancyGrid::SharedPtr msg) {
  cv::Mat grid(
    static_cast<int>(msg->info.height), static_cast<int>(msg->info.width), CV_8SC1,
    const_cast<int8_t *>(msg->data.data())
  );
  
  cv::Mat occupied = grid >= p_occupied;
  cv::Mat unknown = grid < 0;

  cv::Mat freeMask = ~occupied; 
  cv::Mat dist; 
  cv::distanceTransform(freeMask, dist, cv::DIST_L2, cv::DIST_MASK_PRECISE);
  dist *= config_occgrid_resolution;  

  cv::Mat cost;
  cv::exp((dist - radius_inscribed) * (-scale_cost), cost);
  cost *= (cost_inscribed - 1); 
  cost.setTo(0, dist > radius_inflation);
  cost.setTo(cost_inscribed, dist <= radius_inscribed);
 
  cost.setTo(cost_lethal, occupied);
  cv::Mat out;
  cost.convertTo(out, CV_8U);
  out.setTo(cost_unknown, unknown);
  return out;
}



int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CostMap>());
  rclcpp::shutdown();
  return 0;
}
