//
// Created by mihau on 11/10/15.
//

#ifndef PONG_ARDUINO_MOCK_BOARD_H
#define PONG_ARDUINO_MOCK_BOARD_H

#include "renderer.h"
#include "color.h"
#include "gameObject.h"


class Board: GameObject {
private:
    int w;
    int h;
    int thickness;
public:
    Board(int width, int height, int thickness);

    int getWidth() const;

    int getHeight() const;

    int getMiddleX() const;

    int getMiddleY() const;

    void update();

    void render(Renderer* r);

};

#endif //PONG_ARDUINO_MOCK_BOARD_H
