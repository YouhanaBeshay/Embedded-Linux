#include <condition_variable>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vsomeip/vsomeip.hpp>

constexpr static vsomeip::service_t SERVICE_ID = 4666;
constexpr static vsomeip::instance_t INSTANCE_ID = 1;
constexpr static vsomeip::method_t METHOD_ID = 1;

class vsomeip_service {
private:
  std::shared_ptr<vsomeip::runtime> rtm_;
  std::shared_ptr<vsomeip::application> app_;
  // bool stop_;
  // std::mutex mutex_;
  // std::condition_variable condition_;
  // std::thread stop_thread_;

public:
  vsomeip_service()
      : rtm_(vsomeip::runtime::get()),
        app_(rtm_->create_application("CapsLock Service")) {

    app_->init();
    // fire and forget message handler
    app_->register_message_handler(
        SERVICE_ID, INSTANCE_ID, METHOD_ID,
        [this](const std::shared_ptr<vsomeip::message> &msg) {
          std::cout << "Received request" << std::endl;
          if (msg->get_payload()->get_data()[0] == '1') {
            std::fstream file;
            std::cout << "Received 1" << std::endl;
            file.open("/sys/class/leds/input7::capslock/brightness",
                      std::ios::out);
            file << "1";
            file.close();

          } else if (msg->get_payload()->get_data()[0] == '0') {
            std::fstream file;
            std::cout << "Received 0" << std::endl;
            file.open("/sys/class/leds/input7::capslock/brightness",
                      std::ios::out);
            file << "0";
            file.close();
          } else {
            std::cout << "Received unknown value" << std::endl;
          }
        });

    // handler for request_service
    app_->register_state_handler([this](vsomeip::state_type_e state) {
      if (state == vsomeip::state_type_e::ST_REGISTERED) {
        std::cout << "Service is registered" << std::endl;
        app_->offer_service(SERVICE_ID, INSTANCE_ID);
      }
    });
  }

  void start() { app_->start(); }

  ~vsomeip_service() { app_->stop(); }
};