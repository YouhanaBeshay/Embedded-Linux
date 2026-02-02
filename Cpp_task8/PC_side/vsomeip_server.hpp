#include <condition_variable>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vsomeip/vsomeip.hpp>

constexpr static vsomeip::service_t SERVICE_ID = 0x4666;
constexpr static vsomeip::instance_t INSTANCE_ID = 0x0001;
constexpr static vsomeip::method_t METHOD_ID = 0x0001;
#define EVENTGROUP_ID 0x4465
#define EVENT_ID 0x8778

class vsomeip_service {
private:
  std::shared_ptr<vsomeip::runtime> rtm_;
  std::shared_ptr<vsomeip::application> app_;
  std::set<vsomeip::eventgroup_t> event_group;
  std::thread read_thread_;

public:
  vsomeip_service()
      : rtm_(vsomeip::runtime::get()),
        app_(rtm_->create_application("CapsLock Service")) {

    app_->init();

    // handler for request_service
    app_->register_state_handler([this](vsomeip::state_type_e state) {
      if (state == vsomeip::state_type_e::ST_REGISTERED) {
        std::cout << "Service is registered" << std::endl;

        app_->offer_service(SERVICE_ID, INSTANCE_ID);

        event_group.insert(EVENTGROUP_ID);
        app_->offer_event(SERVICE_ID, INSTANCE_ID, EVENT_ID, event_group);
      }
    });
  }

  void start() {
    // start read thread

    read_thread_ = std::thread(&vsomeip_service::readCapsLock, this);

    // start application
    app_->start();
  }

  void readCapsLock() {
    while (1) {
      std::fstream file;
      std::string value;
      file.open("/sys/class/leds/input7::capslock/brightness", std::ios::in);
      file >> value;
      file.close();
      std::shared_ptr<vsomeip::payload> payload;

      payload = rtm_->create_payload();
      if (value == "1") {
        vsomeip::byte_t payload_data[] = {1};
        payload->set_data(payload_data, sizeof(payload_data));
      } else {
        vsomeip::byte_t payload_data[] = {0};
        payload->set_data(payload_data, sizeof(payload_data));
      }
      app_->notify(SERVICE_ID, INSTANCE_ID, EVENT_ID, payload);
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }

  ~vsomeip_service() {
    if (read_thread_.joinable()) {
      read_thread_.join();
    }
    app_->stop();
  }
};