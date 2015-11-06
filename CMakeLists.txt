cmake_minimum_required(VERSION 3.3)
project(pong_arduino_mock)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

set(SFML_LIBRARIES /usr/lib)
set(SFML_INCLUDE_DIRS /usr/include/SFML)

include_directories(${SFML_INCLUDE_DIRS})
add_executable(pong_arduino_mock ${SOURCE_FILES})
link_directories(/usr/lib)