//
// Created by mihau on 11/15/15.
//

#include "joystickInputDevice.h"

JoystickInputDevice::JoystickInputDevice(int pin) {
    this->pin = pin;
}

int JoystickInputDevice::getAngle() {
    return analogRead(this->pin) - 512;
}
