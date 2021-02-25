cmake_minimum_required(VERSION 3.5.1)

project(Study_Demo)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")

add_compile_options(-std=c++17)

include_directories(./imgui)

find_library(dl REQUIRED)
find_library(X11 REQUIRED)
find_library(GL REQUIRED)

aux_source_directory(./imgui IMGUI_SRC)
# cxxopts sample 
add_executable(imgui_demo1 imgui_demo1.cpp ${IMGUI_SRC})
target_link_libraries(imgui_demo1 GLEW glfw GL)
add_executable(imgui_demo2 imgui_demo2.cpp ${IMGUI_SRC})
target_link_libraries(imgui_demo2 GLEW glfw GL)