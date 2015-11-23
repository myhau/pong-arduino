//
// Created by mihau on 11/10/15.
//


#include "frameRate.h"


#ifndef ARDUINO
#include <sys/time.h>
#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>
long int FrameRateHandler::nowInUs() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000000 + tp.tv_usec;
    return ms;
}

FrameRateHandler::FrameRateHandler(int frameRate):
        frameRate(frameRate), lastUpdate(0),
        shouldUpdateEvery(1000000 / frameRate) {}

void FrameRateHandler::updatedFrameNow() {
    lastUpdate = nowInUs();
}
bool FrameRateHandler::shouldUpdateFrame() {
    long timeLeft = shouldUpdateEvery - (nowInUs() - lastUpdate);

    if(timeLeft > 0) {
        timeLeft = std::min(timeLeft, shouldUpdateEvery);
        usleep(timeLeft);
    }
    return true;
}
#else 
long int FrameRateHandler::nowInUs() {
    return 0;
}

FrameRateHandler::FrameRateHandler(int frameRate):
        frameRate(frameRate), lastUpdate(0),
        shouldUpdateEvery(1000000 / frameRate) {}

void FrameRateHandler::updatedFrameNow() {
    
}
bool FrameRateHandler::shouldUpdateFrame() {
    return true;
}
#endif