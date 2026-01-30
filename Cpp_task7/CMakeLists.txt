cmake_minimum_required (VERSION 3.13)

set (CMAKE_CXX_FLAGS "-g -std=c++0x")

find_package (vsomeip3 3.4.10 REQUIRED)
find_package( Boost 1.55 COMPONENTS system thread log REQUIRED )

include_directories (
    ${Boost_INCLUDE_DIR}
    ${VSOMEIP_INCLUDE_DIRS}
)

add_executable(vsomeip_service vsomeip_service.cpp)

target_link_libraries(vsomeip_service vsomeip3 ${Boost_LIBRARIES})

add_executable(vsomeip_client vsomeip_client.cpp)
target_link_libraries(vsomeip_client vsomeip3 ${Boost_LIBRARIES})