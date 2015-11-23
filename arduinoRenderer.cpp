//
// Created by mihau on 11/10/15.
//

#include "arduinoRenderer.h"
void ArduinoRenderer::after() {
    TV.delay(50);
}

ArduinoRenderer::ArduinoRenderer(int w, int h) {
    this->w = w;
    this->h = h;
    TV.begin(PAL, w, h);
}

int ArduinoRenderer::screenWidth() {
    return this->w;
}
int ArduinoRenderer::screenHeight() {
    return this->h;
}

void ArduinoRenderer::drawRect(int x0, int y0, int w1, int h1, Color c, bool filled) {
    if(filled)
        TV.draw_rect(x0, y0, w1, h1, WHITE, INVERT);
    else
        TV.draw_rect(x0, y0, w1, h1, WHITE);
    this->after();
}

void ArduinoRenderer::drawCircle(int x, int y, int r, Color c, bool filled) {
    if(filled)
        TV.draw_circle(x, y, r, WHITE,INVERT);
    else
        TV.draw_circle(x, y, r, WHITE);
    this->after();
};
void ArduinoRenderer::clearScreen(Color c) {
    TV.clear_screen();
//    this->after();
};

