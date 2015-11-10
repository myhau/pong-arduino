//
// Created by mihau on 11/10/15.
//

#ifndef PONG_ARDUINO_MOCK_RENDERER_H
#define PONG_ARDUINO_MOCK_RENDERER_H

#include "color.h"

class Renderer {
public:
    virtual void drawRect(int x, int y, int width, int height, Color c, bool filled = false) = 0;
    virtual void drawCircle(int x, int y, int radius, Color c, bool filled = false) = 0;
    virtual void clearScreen(Color c) = 0;
    virtual int screenWidth() = 0;
    virtual int screenHeight() = 0;
};

#endif //PONG_ARDUINO_MOCK_RENDERER_H
