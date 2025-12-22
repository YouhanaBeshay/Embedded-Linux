cmake_minimum_required(VERSION 3.15)

project(sevneseg CXX)


add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../../Cpp_task3/lib/  ${CMAKE_CURRENT_BINARY_DIR}/lib )

add_library(sevneseg SHARED Stream.cpp Istream.cpp Ostream.cpp IOstream.cpp SevenSegments.cpp)


target_include_directories(sevneseg PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../inc)

target_link_libraries(sevneseg PUBLIC mygpio)

