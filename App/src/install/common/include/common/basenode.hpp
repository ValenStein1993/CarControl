#pragma once
#include <vector>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "common/config.hpp"


class BaseNode : public rclcpp::Node {
    public:
        BaseNode(const std::string& node_name)
          : rclcpp::Node(node_name) 
        {
            declare_parameter<bool>("debug", false);
            get_parameter("debug", debug_);
        }

        bool debug_;
        std::vector<rclcpp::TimerBase::SharedPtr> timers_;

        template <typename Rep, typename Period, typename Class>
        void add_timer(std::chrono::duration<Rep, Period> period,
            void (Class::*callback)()) 
        {
            timers_.push_back(create_wall_timer(period,
                std::bind(callback, static_cast<Class*>(this)))
            );
        }

};