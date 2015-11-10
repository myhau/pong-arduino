#!/bin/sh
mkdir -p compile; 
cd compile
cmake ..
make 
cp pong_arduino_mock ..
cd ..