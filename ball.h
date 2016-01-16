//
// Created by mihau on 11/10/15.
//

#ifndef PONG_ARDUINO_MOCK_BALL_H
#define PONG_ARDUINO_MOCK_BALL_H


#include "gameObject.h"
#include "board.h"
#include "paddle.h"
#include "gameStatus.h"
#include "color.h"

#include "soundOutput.h"

#include "random.h"


class Ball: public GameObject {

private:
    float radius;
    float velocity_x;
    float velocity_y;
    float pos_x;
    float pos_y;
    Board* board;
    Paddle* paddle1;
    Paddle* paddle2;
    GameStatus* gameStatus;
    SoundOutput* s1;
    Sound* soundPaddle;
    Sound* soundBoard;

public:
    void setVelocity_x(float velocity_x);

    void setVelocity_y(float velocity_y);

    void setPos_x(float pos_x);

    void setPos_y(float pos_y);

    bool didCollide(Paddle* p);
    bool didCollide(Board* b);

    Ball(float radius, Board* b, Paddle* paddle1, Paddle* paddle2, GameStatus* gameStatus, SoundOutput*);

    Ball(float radius, float initial_pos_x, float initial_pos_y, Board* b, Paddle* paddle1, Paddle* paddle2, GameStatus* gameStatus, SoundOutput*);

    void update();
    void render(Renderer* r);

private:
    void handleCollision(Paddle* p);
    void handleCollision(Board* b);


};




#endif //PONG_ARDUINO_MOCK_BALL_H
