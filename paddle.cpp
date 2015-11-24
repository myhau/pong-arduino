//
// Created by mihau on 11/10/15.
//



// #include <iostream>
#include "paddle.h"


Paddle::Paddle(Paddle::Which which, float paddle_width, float paddle_height, Board* b, InputDevice* device1):
        device(device1), board(b), which_paddle(which),
        w(paddle_width), h(paddle_height), velocity_y(0), pos_y(1) {
    pos_x = (which_paddle == left) ? 0 : board->getWidth() - w;
}


float Paddle::getVelocityY() const {
    return velocity_y;
}

float Paddle::getWidth() const {
    return w;
}

float Paddle::getHeight() const {
    return h;
}

float Paddle::getPosY() const {
    return pos_y;
}

float Paddle::getPosX() const {
    return pos_x;
}


void Paddle::setPos_y(float pos_y) {
    this->pos_y = pos_y;
}

void Paddle::setPos_x(float pos_x) {
    this->pos_x = pos_x;
}

void Paddle::setVelocity_y(float velocity_y) {
    this->velocity_y = velocity_y;
}

Paddle::Which Paddle::getWhichPaddle() const {
    return which_paddle;
}

void Paddle::update() {
    velocity_y = (device->getAngle()/400.0);
    pos_y += velocity_y;
    if(pos_y + h > board->getHeight()) {
        velocity_y = 0;
        pos_y = board->getHeight() - h - 1;
    }
    else if(pos_y < 0) pos_y = 1;
}
void Paddle::render(Renderer* r) {

    r->drawRect(pos_x, pos_y, w, h, Color::White, true);
}