cmake_minimum_required(VERSION 3.5.1)

project(Study_Demo)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")

add_compile_options(-std=c++17)

add_subdirectory(./rpc ./rpc)

include_directories(./rpc/include)

list(APPEND LINK_LIB rpc pthread)

# rpclib sample 
add_executable(rpclib_client_demo rpclib_client.cpp)
target_link_libraries(rpclib_client_demo ${LINK_LIB})
add_executable(rpclib_server_demo rpclib_server.cpp)
target_link_libraries(rpclib_server_demo ${LINK_LIB})
