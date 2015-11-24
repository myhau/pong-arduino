//
// Created by mihau on 11/15/15.
//

#ifndef PONG_ARDUINO_MOCK_ARDUINORENDERER_H
#define PONG_ARDUINO_MOCK_ARDUINORENDERER_H


#include "renderer.h"
#include "inputDevice.h"
#include "TVout.h"
#include "Arduino.h"

class ArduinoRenderer: public Renderer {
private:
    int w;
    int h;
public:
    TVout TV;

void after();
public:
    ArduinoRenderer(int width, int height);
    virtual void drawRect(int x, int y, int width, int height, Color c, bool filled) override;

    virtual void drawCircle(int x, int y, int radius, Color c, bool filled) override;

    virtual void clearScreen(Color c) override;

    virtual int screenWidth() override;

    virtual int screenHeight() override;
};


#endif //PONG_ARDUINO_MOCK_ARDUINORENDERER_H
