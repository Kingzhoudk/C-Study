cmake_minimum_required(VERSION 3.5.1)

project(Study_Demo)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")

add_compile_options(-std=c++17)


list(APPEND LINK_LIB atomic pthread)

add_executable(study_atomic study_atomic.cpp)
target_link_libraries(study_atomic ${LINK_LIB})

