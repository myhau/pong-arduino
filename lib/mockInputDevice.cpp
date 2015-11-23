//
// Created by mihau on 11/10/15.
//

#include "mockInputDevice.h"

MockInputDevice::MockInputDevice(): angle(0) {

}

int MockInputDevice::getAngle() {
    return angle;
}

void MockInputDevice::setAngle(int angle) {
    this->angle = angle;
}