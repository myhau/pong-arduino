//
// Created by mihau on 11/15/15.
//

#include <stdlib.h>
#include "randomInputDevice.h"

int randomInputDevice::getAngle() {
    int nowTime = randomInputDevice::nowTime();


    if(nowTime - this->prevTime > 1) {
        this->prevTime = nowTime;
        this->angle = (-this->angle + rand() % 512) % 1024 - 512;
    }

    return this->angle;
}
