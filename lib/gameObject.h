//
// Created by mihau on 11/10/15.
//

#ifndef PONG_ARDUINO_MOCK_GAMEOBJECT_H
#define PONG_ARDUINO_MOCK_GAMEOBJECT_H


#include "renderer.h"

class GameObject {
    virtual void update() = 0;
    virtual void render(Renderer* r) = 0;
};

#endif //PONG_ARDUINO_MOCK_GAMEOBJECT_H
