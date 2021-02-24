cmake_minimum_required(VERSION 3.5.1)

project(Study_Demo)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")

add_compile_options(-std=c++17)

# mqtt sample
# sudo apt install libmosquitto-dev
add_executable(mqtt_publish_demo mqtt_publish_demo.cpp)
target_link_libraries(mqtt_publish_demo mosquitto)
add_executable(mqtt_publish_demo2 mqtt_publish_demo2.cpp)
target_link_libraries(mqtt_publish_demo2 mosquitto)
add_executable(mqtt_subscribed_demo mqtt_subscribed_demo.cpp)
target_link_libraries(mqtt_subscribed_demo mosquitto)
