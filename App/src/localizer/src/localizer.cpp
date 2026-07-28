#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "car_msgs/msg/sensor_data.hpp"

using std::placeholders::_1;

class Localizer : public rclcpp::Node
{
  public:
    Localizer(): Node("localizer") {
      subscription_ = create_subscription<car_msgs::msg::SensorData>(
      "/sensor_data", 10, std::bind(&Localizer::topic_callback, this, _1));
    }

  private:
    void topic_callback(const car_msgs::msg::SensorData::SharedPtr msg) const {
      RCLCPP_INFO(this->get_logger(), "I heard: '%f'", msg->angle);
    }
    rclcpp::Subscription<car_msgs::msg::SensorData>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Localizer>());
  rclcpp::shutdown();
  return 0;
}