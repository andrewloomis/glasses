cmake_minimum_required(VERSION 2.8)
project(glasses)

set(SOURCES src/main.cpp src/gesture.cpp)
set(CMAKE_BUILD_TYPE Debug)

add_executable(glasses ${SOURCES})
target_link_libraries(glasses mraa)
target_include_directories(glasses PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
