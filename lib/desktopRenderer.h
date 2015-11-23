//
// Created by mihau on 11/10/15.
//

#ifndef PONG_ARDUINO_MOCK_DESKTOPRENDERER_H
#define PONG_ARDUINO_MOCK_DESKTOPRENDERER_H

#include <SFML/Graphics.hpp>
#include "renderer.h"
#include "inputDevice.h"
#include "color.h"
#include "mockInputDevice.h"

using namespace std;

class DesktopRenderer: public Renderer {
private:
    int w;
    int h;
    sf::RenderWindow window;
    MockInputDevice mockInputDevice;

public:
    DesktopRenderer(int w, int h);
    InputDevice* getInputDevice();

    int screenWidth();
    int screenHeight();

    void check_and_clear();

    void draw_window();

    void drawRect(int x0, int y0, int w1, int h1, Color c, bool filled = false) override;

    // x, y is center
    void drawCircle(int x, int y, int r, Color c, bool filled = false) override;
    void clearScreen(Color c) override;

};


#endif //PONG_ARDUINO_MOCK_DESKTOPRENDERER_H
