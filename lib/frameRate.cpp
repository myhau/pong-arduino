//
// Created by mihau on 11/10/15.
//

#include <sys/time.h>
#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include "frameRate.h"



long int FrameRateHandler::nowInUs() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000000 + tp.tv_usec;
    return ms;
}

FrameRateHandler::FrameRateHandler(uint8_t frameRate):
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