cmake_minimum_required(VERSION 3.5.1)

project(Study_Demo)

add_compile_options(-std=c++17 -Wall -Werror)

add_subdirectory(3rdparty/rpc 3rdparty/rpc)

include_directories(
                    3rdparty/Box2D
                    3rdparty/cxxopts
                    3rdparty/nlohmann
                    3rdparty/rpc/include
                    3rdparty/websocketpp
                    src)


list(APPEND LINK_LIB rpc glog atomic pthread -flto)

file(GLOB_RECURSE Box2D_SRC 3rdparty/Box2D/*.cpp)
add_executable(BOX2D_demo ${Box2D_SRC} src/Box2D_demo2.cpp )
target_link_libraries(BOX2D_demo ${LINK_LIB})


add_executable(cxxopts_demo src/cxxopts.cpp)


add_executable(rpclib_client_demo src/rpclib_client.cpp)
target_link_libraries(rpclib_client_demo ${LINK_LIB})
add_executable(rpclib_server_demo src/rpclib_server.cpp)
target_link_libraries(rpclib_server_demo ${LINK_LIB})