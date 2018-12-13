cmake_minimum_required(VERSION 3.5)
project(scope_guard)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

add_subdirectory(lib/googletest)

include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES testing.cpp)
add_executable(scope_guard ${SOURCE_FILES})
target_link_libraries(scope_guard gtest gtest_main)