cmake_minimum_required(VERSION 3.3)
project(pong_arduino_mock)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ball.h ball.cpp paddle.h paddle.cpp desktopRenderer.cpp desktopRenderer.h renderer.h board.cpp board.h
        frameRate.h frameRate.cpp game.h game.cpp gameObject.h inputDevice.h mockInputDevice.cpp mockInputDevice.h gameConfig.cpp gameConfig.h color.h gameStatus.h)

set(SFML_LIBRARIES sfml/bin)
set(SFML_INCLUDE_DIRS sfml/include)

include_directories(${SFML_INCLUDE_DIRS})
add_executable(pong_arduino_mock ${SOURCE_FILES})
link_directories(${SFML_LIBRARIES})
target_link_libraries(pong_arduino_mock sfml-graphics sfml-window sfml-system)
