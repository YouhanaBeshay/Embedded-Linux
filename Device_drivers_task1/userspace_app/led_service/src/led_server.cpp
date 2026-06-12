#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/trigger.hpp>

#include <fcntl.h>
#include <unistd.h>

using Trigger = std_srvs::srv::Trigger;

class GpioServiceNode : public rclcpp::Node {
public:
  GpioServiceNode() : Node("gpio_service_node") {
    gpio_path_ = "/proc/rpi_gpio";

    srv_on_ = this->create_service<Trigger>(
        "gpio_on", std::bind(&GpioServiceNode::handle_on, this,
                             std::placeholders::_1, std::placeholders::_2));

    srv_off_ = this->create_service<Trigger>(
        "gpio_off", std::bind(&GpioServiceNode::handle_off, this,
                              std::placeholders::_1, std::placeholders::_2));

    RCLCPP_INFO(this->get_logger(), "GPIO Service Node Ready");
  }

private:
  std::string gpio_path_;

  rclcpp::Service<Trigger>::SharedPtr srv_on_;
  rclcpp::Service<Trigger>::SharedPtr srv_off_;

  bool write_gpio(const std::string &value) {
    int fd = open(gpio_path_.c_str(), O_WRONLY);
    if (fd < 0) {
      return false;
    }

    ssize_t ret = write(fd, value.c_str(), 1); 
    close(fd);

    return ret == 1;
  }

  void handle_on(const std::shared_ptr<Trigger::Request>,
                 std::shared_ptr<Trigger::Response> response) {
    if (write_gpio("1")) {
      response->success = true;
      response->message = "OK";
    } else {
      response->success = false;
      response->message = "FAIL";
    }
  }

  void handle_off(const std::shared_ptr<Trigger::Request>,
                  std::shared_ptr<Trigger::Response> response) {
    if (write_gpio("0")) {
      response->success = true;
      response->message = "OK";
    } else {
      response->success = false;
      response->message = "FAIL";
    }
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<GpioServiceNode>());
  rclcpp::shutdown();
  return 0;
}