cmake_minimum_required(VERSION 3.3)
project(pong_arduino_mock_lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ball.h ball.cpp paddle.h paddle.cpp desktopRenderer.cpp desktopRenderer.h renderer.h board.cpp board.h
        frameRate.h frameRate.cpp game.h game.cpp gameObject.h inputDevice.h mockInputDevice.cpp mockInputDevice.h gameConfig.cpp gameConfig.h color.h gameStatus.h randomInputDevice.cpp randomInputDevice.h)

set(SFML_LIBRARIES sfml/bin)
set(SFML_INCLUDE_DIRS sfml/include)

add_definitions(-DDESKTOP)

include_directories(${SFML_INCLUDE_DIRS})
include_directories(/usr/share/arduino/hardware/arduino/avr/cores/arduino)
include_directories(../arduino-lib)
add_library(pong_arduino_mock_lib ${SOURCE_FILES})
link_directories(${SFML_LIBRARIES})
target_link_libraries(pong_arduino_mock_lib sfml-graphics sfml-window sfml-system)
