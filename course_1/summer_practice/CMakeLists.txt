cmake_minimum_required(VERSION 3.5)
project(scope_guard)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

set(SOURCE_FILES main.cpp)
add_executable(scope_guard ${SOURCE_FILES})