#include "custom_interfaces/srv/get_battery.hpp"
#include "rclcpp/rclcpp.hpp"

void get_battery([[maybe_unused]] const std::shared_ptr<custom_interfaces::srv::GetBattery::Request> request,
                 std::shared_ptr<custom_interfaces::srv::GetBattery::Response> response) {
    // Dummy battery level
    auto battery_level = 75;
    response->battery = battery_level;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]",
                (long int)response->battery);
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("get_battery_server");

  auto service = node->create_service<custom_interfaces::srv::GetBattery>(
      "get_battery", &get_battery);

  rclcpp::spin(node);
  rclcpp::shutdown();
}
