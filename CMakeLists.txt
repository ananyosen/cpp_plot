cmake_minimum_required(VERSION 2.8.9)
project(cpp_plot)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/builds)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/libs)

#Headers
include_directories(include)

set(SOURCES src/plot.cpp)

#add_executable(testStudent ${SOURCES})