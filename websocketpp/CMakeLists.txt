cmake_minimum_required(VERSION 3.5.1)

project(Study_Demo)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")

add_compile_options(-std=c++17)

include_directories(./websocketpp)

list(APPEND LINK_LIB boost_system pthread)

# websocketpp sample
add_executable(websocketpp_server_demo websocketpp_demo_server.cpp)
target_link_libraries(websocketpp_server_demo ${LINK_LIB})
add_executable(websocketpp_client_demo websocketpp_demo_client.cpp)
target_link_libraries(websocketpp_client_demo ${LINK_LIB})
