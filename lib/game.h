//
// Created by mihau on 11/10/15.
//

#ifndef PONG_ARDUINO_MOCK_GAME_H
#define PONG_ARDUINO_MOCK_GAME_H

#include "board.h"
#include "ball.h"
#include "paddle.h"
#include "renderer.h"
#include "frameRate.h"
#include "gameConfig.h"
#include "gameStatus.h"

class Game {
private:
    Board* board;
    Ball* ball;
    Paddle* paddle1;
    Paddle* paddle2;
    Renderer* renderer;
    FrameRateHandler* frh;
    GameStatus* gameStatus;
    int player1Score;
    int player2Score;
public:
    Game(Renderer *renderer, GameConfig *gameConfig, InputDevice *inputDevice1, InputDevice *inputDevice2);

    void restartAndUpdateScores(int player1, int player2);

    void oneFrame();

    void start();

    void stop();
};

#endif //PONG_ARDUINO_MOCK_GAME_H
