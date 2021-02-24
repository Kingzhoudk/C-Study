cmake_minimum_required(VERSION 3.5.1)

project(Study_Demo)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")

add_compile_options(-std=c++17 -Wall -Werror)

include_directories(./Box2D)


list(APPEND LINK_LIB glog atomic pthread -flto)

# box2d sample 
file(GLOB_RECURSE Box2D_SRC Box2D/*.cpp)
add_executable(box2d_demo1 ${Box2D_SRC} box2d_demo.cpp )
target_link_libraries(box2d_demo1 ${LINK_LIB})
add_executable(box2d_demo2 ${Box2D_SRC} box2d_demo2.cpp )
target_link_libraries(box2d_demo2 ${LINK_LIB})
add_executable(box2d_demo3 ${Box2D_SRC} box2d_demo3.cpp )
target_link_libraries(box2d_demo3 ${LINK_LIB})
