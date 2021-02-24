cmake_minimum_required(VERSION 3.5.1)

project(Study_Demo)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")

add_compile_options(-std=c++17 -Wall -Werror)

include_directories(./cxxopts)

# cxxopts sample 
add_executable(cxxopts_demo cxxopts.cpp)
