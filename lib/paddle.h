//
// Created by mihau on 11/10/15.
//

#ifndef PONG_ARDUINO_MOCK_PADDLE_H
#define PONG_ARDUINO_MOCK_PADDLE_H

#include "board.h"
#include "inputDevice.h"

class Paddle: GameObject {
public:
    typedef char Which;
private:
    Which which_paddle;
    float w;
    float h;
    float velocity_y;
    float pos_y;
    float pos_x;
    Board* board;
    InputDevice* device;
public:
    static const Which left = 0;
    static const Which right = 1;

    Paddle(Which which, float paddle_width, float paddle_height, Board* b, InputDevice* device1);


    float getVelocityY() const;

    float getWidth() const;

    float getHeight() const;

    float getPosY() const;

    float getPosX() const;


    void setPos_y(float pos_y);

    void setPos_x(float pos_x);

    void setVelocity_y(float velocity_y);

    Which getWhichPaddle() const;

    void update() override;
    void render(Renderer* r) override;
};

#endif //PONG_ARDUINO_MOCK_PADDLE_H
