#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>
#include <vsomeip/vsomeip.hpp>

#include <fstream>
#include <iostream>

constexpr static vsomeip::service_t SERVICE_ID = 4666;
constexpr static vsomeip::instance_t INSTANCE_ID = 1;
constexpr static vsomeip::method_t METHOD_ID = 1;

class vsomeip_client {
private:
  std::shared_ptr<vsomeip::runtime> rtm_;
  std::shared_ptr<vsomeip::application> app_;
  // bool stop_;
  // std::mutex mutex_;
  // std::condition_variable condition_;
  std::thread send_thread_;

public:
  vsomeip_client()
      : rtm_(vsomeip::runtime::get()),
        app_(rtm_->create_application("CapsLock client")) {

    app_->init();
    // state handler
    app_->register_state_handler([this](vsomeip::state_type_e state) {
      if (state == vsomeip::state_type_e::ST_REGISTERED) {
        std::cout << "Client is ready" << std::endl;
        app_->request_service(SERVICE_ID, INSTANCE_ID);
      }
    });
    app_->register_availability_handler(
        SERVICE_ID, INSTANCE_ID,
        [this](vsomeip::service_t service, vsomeip::instance_t instance,
               bool is_available) {
          std::cout << "Service is available" << std::endl;
          if (service == SERVICE_ID && instance == INSTANCE_ID &&
              is_available) {
            if (!send_thread_.joinable()) { // Check if thread already exists
              send_thread_ = std::thread(&vsomeip_client::sendRequest, this);
            }
          }
        });
  }
  void start() { app_->start(); }

  void sendRequest() {
    while (true) {

      // create the request

      std::shared_ptr<vsomeip::message> request;
      request = rtm_->create_request();
      request->set_service(SERVICE_ID);
      request->set_instance(INSTANCE_ID);
      request->set_method(METHOD_ID);

      // get the payload from user
      std::cout << "Sending request: please enter the payload 'char'"
                << std::endl;
      std::cout.flush();

      std::string input;
      if (!std::getline(std::cin, input)) {
        stop();
        break;
      }

      if (input.empty()) {
        continue;
      }

      char ch = input[0];

      auto payload = rtm_->create_payload();
      std::vector<vsomeip::byte_t> payload_data;

      payload_data.push_back(ch);
      payload->set_data(payload_data);

      request->set_payload(payload);

      app_->send(request);
    }
  }

  void stop() {
    app_->clear_all_handler();
    
    app_->release_service(SERVICE_ID, INSTANCE_ID);

    app_->stop();
  }

  ~vsomeip_client() {
    if (send_thread_.joinable()) {

      send_thread_.join();
    }

    app_->stop();
  }
};