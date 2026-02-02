#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>
#include <vsomeip/vsomeip.hpp>

#include <fstream>
#include <iostream>

constexpr static vsomeip::service_t SERVICE_ID = 0x4666;
constexpr static vsomeip::instance_t INSTANCE_ID = 0x0001;
constexpr static vsomeip::method_t METHOD_ID = 0x0001;
#define EVENTGROUP_ID 0x4465
#define EVENT_ID 0x8778
class vsomeip_client {
private:
  std::shared_ptr<vsomeip::runtime> rtm_;
  std::shared_ptr<vsomeip::application> app_;
  std::set<vsomeip::eventgroup_t> event_group;

public:
  vsomeip_client()
      : rtm_(vsomeip::runtime::get()),
        app_(rtm_->create_application("CapsLock client")) {

    app_->init();

    event_group.insert(EVENTGROUP_ID);

    // state handler
    app_->register_state_handler([this](vsomeip::state_type_e state) {
      if (state == vsomeip::state_type_e::ST_REGISTERED) {
        std::cout << "Client is ready" << std::endl;
        app_->request_service(SERVICE_ID, INSTANCE_ID);
        // request event
        app_->request_event(SERVICE_ID, INSTANCE_ID, EVENT_ID, event_group);
      }
    });

    app_->register_availability_handler(
        SERVICE_ID, INSTANCE_ID,
        [this](vsomeip::service_t service, vsomeip::instance_t instance,
               bool is_available) {
          std::cout << "Service is available" << std::endl;
          if (service == SERVICE_ID && instance == INSTANCE_ID &&
              is_available) {
            // subscribe
            app_->subscribe(SERVICE_ID, INSTANCE_ID, EVENTGROUP_ID);
          }
        });

    // message handler ( for event notification )
    app_->register_message_handler(
        SERVICE_ID, INSTANCE_ID, vsomeip::ANY_METHOD,
        [this](const std::shared_ptr<vsomeip::message> &notification) {
          auto payload = notification->get_payload();
          std::cout << "Received notification" << std::endl;
          if ((int)payload->get_data()[0] == 1) {
            std::cout << "CapsLock is on" << std::endl;

          } else {
            std::cout << "CapsLock is off" << std::endl;
          }
        });
  }
  void start() { app_->start(); }

  void stop() {
    app_->clear_all_handler();

    app_->release_event(SERVICE_ID, INSTANCE_ID, EVENT_ID);

    app_->stop();
  }

  ~vsomeip_client() { app_->stop(); }
};