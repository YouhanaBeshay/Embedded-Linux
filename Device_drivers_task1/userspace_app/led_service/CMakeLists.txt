cmake_minimum_required(VERSION 3.8)
project(led_service)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_srvs REQUIRED)

add_executable(led_server src/led_server.cpp)
ament_target_dependencies(led_server rclcpp std_srvs)


install(TARGETS led_server 
  DESTINATION lib/${PROJECT_NAME})

ament_package()
