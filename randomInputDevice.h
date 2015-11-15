//
// Created by mihau on 11/15/15.
//

#ifndef PONG_ARDUINO_MOCK_RANDOMINPUTDEVICE_H
#define PONG_ARDUINO_MOCK_RANDOMINPUTDEVICE_H


#include "inputDevice.h"

#include <ctime>


class randomInputDevice: public InputDevice {
private:
    int prevTime;
    int angle;
public:
    randomInputDevice(): InputDevice() {
        angle = 0;
        prevTime = 0;
    }
    virtual int getAngle() override;
};


#endif //PONG_ARDUINO_MOCK_RANDOMINPUTDEVICE_H
