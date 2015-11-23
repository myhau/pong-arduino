//
// Created by mihau on 11/15/15.
//

#ifndef PONG_ARDUINO_MOCK_JOYSTICKINPUTDEVICE_H
#define PONG_ARDUINO_MOCK_JOYSTICKINPUTDEVICE_H


#include "inputDevice.h"
#include <Arduino.h>

class JoystickInputDevice: public InputDevice {
private:
    int pin;
public:
    JoystickInputDevice(int pin);

    virtual int getAngle() override;

};


#endif //PONG_ARDUINO_MOCK_JOYSTICKINPUTDEVICE_H
