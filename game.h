//
// Created by mihau on 11/10/15.
//

#ifndef PONG_ARDUINO_MOCK_GAME_H
#define PONG_ARDUINO_MOCK_GAME_H

#include <Arduino.h>

#include "board.h"
#include "ball.h"
#include "paddle.h"
#include "renderer.h"
#include "frameRate.h"
#include "gameConfig.h"
#include "gameStatus.h"
#include "random.h"
#include "soundOutput.h"


class Game {
private:
    Board* board;
    Ball* ball;
    Paddle* paddle1;
    Paddle* paddle2;
    Renderer* renderer;
    FrameRateHandler* frh;
    GameStatus* gameStatus;
    InputDevice* inputDevice2;
    int player1Score;
    int player2Score;
    char scoreBuff[16];
    const char* player1won = "Player 1 won !";
    const char* player2won = "Player 2 won !";
    char playerWon[32];
    int nextBallXVelocity;
    bool newRound;
    bool stopBall;
    unsigned long lastStoppedBall;
    SoundOutput* soundOutput;
    Sound* winningSounds[4];
public:
    Game(Renderer *renderer, GameConfig *gameConfig, InputDevice *inputDevice1, InputDevice *inputDevice2);

    void restartAndUpdateScores(int player1, int player2);

    void oneFrame();

    void start();

    void stop();
};

#endif //PONG_ARDUINO_MOCK_GAME_H
