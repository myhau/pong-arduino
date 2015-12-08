//
// Created by mihau on 11/15/15.
//

#include <stdlib.h>
#include "randomInputDevice.h"

#include "Arduino.h"

int randomInputDevice::getAngle() {
    int nowTime = randomInputDevice::nowTime();



    int direction = rand() % 2 - 1;

    if(nowTime - this->prevTime > 100000) {
        this->prevTime = nowTime;
        this->angle = direction * 511;
    }

    return this->angle;
}
