cmake_minimum_required(VERSION 3.5.1)

project(Study_Demo)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")

add_compile_options(-std=c++17 -Wall -Werror)

add_subdirectory(3rdparty/rpc 3rdparty/rpc)

include_directories(
                    3rdparty/Box2D
                    3rdparty/cxxopts
                    3rdparty/nlohmann
                    3rdparty/rpc/include
                    3rdparty/websocketpp
                    3rdparty/mqtt
                    src)


list(APPEND LINK_LIB rpc glog atomic pthread -flto)

# mqtt sample 
file(GLOB_RECURSE Mqtt_SRC 3rdparty/mqtt/*.cpp)
add_executable(mqtt_client_demo ${Mqtt_SRC} src/mqtt_client_demo.cpp)

#[[
# box2d sample 
file(GLOB_RECURSE Box2D_SRC 3rdparty/Box2D/*.cpp)
add_executable(box2d_demo3 ${Box2D_SRC} src/box2d_demo3.cpp )
target_link_libraries(box2d_demo3 ${LINK_LIB})

# cxxopts sample 
add_executable(cxxopts_demo src/cxxopts.cpp)

# rpclib sample 
add_executable(rpclib_client_demo src/rpclib_client.cpp)
target_link_libraries(rpclib_client_demo ${LINK_LIB})
add_executable(rpclib_server_demo src/rpclib_server.cpp)
target_link_libraries(rpclib_server_demo ${LINK_LIB})


list(APPEND LINK_LIB boost_system)
add_executable(websocketpp_server_demo src/websocketpp_demo_server.cpp)
target_link_libraries(websocketpp_server_demo ${LINK_LIB})
add_executable(websocketpp_client_demo src/websocketpp_demo_client.cpp)
target_link_libraries(websocketpp_client_demo ${LINK_LIB})
]]