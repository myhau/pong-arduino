//
// Created by mihau on 11/10/15.
//

#ifndef PONG_ARDUINO_MOCK_MOCKINPUTDEVICE_H
#define PONG_ARDUINO_MOCK_MOCKINPUTDEVICE_H

#include "inputDevice.h"

class MockInputDevice: public InputDevice {
private:
    int angle;
public:
    MockInputDevice();
    int getAngle() override;
    void setAngle(int angle);
};

#endif //PONG_ARDUINO_MOCK_MOCKINPUTDEVICE_H
