cmake_minimum_required(VERSION 2.8.9)
project(cpp_plot)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/builds)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/libs)

#Headers
include_directories(include)

set(SOURCES src/plot.cpp)

set(EXEC_NAME cpp_plt)

add_library(${EXEC_NAME} STATIC ${SOURCES})
#add_executable(cpp_plt ${SOURCES})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXEC_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()