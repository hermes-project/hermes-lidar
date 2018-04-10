cmake_minimum_required(VERSION 3.9)
project(hermes_lidar)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-pthread")
file(GLOB SOURCES "src/*.cpp" "src/*.h" "include/*.h" "include/*.hpp")
include_directories(lib/)
add_executable(hermes_lidar ${SOURCES})
target_link_libraries(hermes_lidar ${CMAKE_SOURCE_DIR}/lib/RPLidar/librplidar_sdk.a)