//
// Created by mihau on 11/15/15.
//

#ifndef PONG_ARDUINO_MOCK_RANDOMINPUTDEVICE_H
#define PONG_ARDUINO_MOCK_RANDOMINPUTDEVICE_H


#include "inputDevice.h"


#ifdef DESKTOP
#include <ctime>
#endif
#ifdef ARDUINO
#include <Arduino.h>
#endif

class randomInputDevice: public InputDevice {
private:
    int prevTime;
    int angle;

    static int nowTime() {
        #ifdef ARDUINO
        return millis() * 1000;
        #endif
        #ifdef DESKTOP
        return (int)(time (NULL));
        #endif
    }
public:
    randomInputDevice(): InputDevice() {
        angle = 0;
        prevTime = 0;
    }
    virtual int getAngle() override;
};


#endif //PONG_ARDUINO_MOCK_RANDOMINPUTDEVICE_H
