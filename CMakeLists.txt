cmake_minimum_required(VERSION 2.8)
project(cpp_plot)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/builds)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_CXX_STANDARD 11)

#Headers
include_directories(include src)

#Sources
#set(SOURCES src/plot.cpp src/plotdata.cpp src/subplot.cpp src/test_tmp.cpp)
set(SOURCES src/test_compile.cpp)

set(EXEC_NAME cpp_plt)

#add_library(${EXEC_NAME} SHARED ${SOURCES})
add_executable(${EXEC_NAME} ${SOURCES})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXEC_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()