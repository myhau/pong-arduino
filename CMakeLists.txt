cmake_minimum_required(VERSION 2.8.4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME pong_arduino_mock)
project(${PROJECT_NAME})

#add_definitions(-DARDUINO)
#remove_definitions(-DDESKTOP)

include_directories(/usr/share/arduino/hardware/arduino/avr/cores/arduino)


file(GLOB project_SRC
        "*.h"
        "*.cpp"
        )

add_executable(whatever ${project_SRC})

add_definitions(-DARDUINO)

#add_subdirectory(lib)

set(${CMAKE_PROJECT_NAME}_SKETCH pong_arduino.ino)
set(${CMAKE_PROJECT_NAME}_BOARD uno)
set(${CMAKE_PROJECT_NAME}_PORT /dev/ttyACM0)

generate_arduino_firmware(${CMAKE_PROJECT_NAME})
