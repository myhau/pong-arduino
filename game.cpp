//
// Created by mihau on 11/10/15.
//

// #include <iostream>
#include "game.h"
#include "bluetoothInputDevice.h"
#include "string.h"
#include "memfree.h"
#include "soundOutput.h"

#ifdef ARDUINO
int rand() {
    return random(10000000);
}
#endif

Game::Game(Renderer* renderer, GameConfig* gameConfig, InputDevice* inputDevice1, InputDevice* inputDevice2):
        renderer(renderer),
        player1Score(0), player2Score(0)
{
    soundOutput = new SoundOutput();
    this->inputDevice2 = inputDevice2;
    gameStatus = new GameStatus;
    board = new Board(gameConfig->boardWidth - 3, gameConfig->boardHeight - 3, 1);
    paddle1 = new Paddle(Paddle::left, gameConfig->paddleWidth, gameConfig->paddleHeight, board, inputDevice1);
    paddle2 = new Paddle(Paddle::right, gameConfig->paddleWidth, gameConfig->paddleHeight, board, inputDevice2);
    ball = new Ball(gameConfig->ballRadius, this->board, this->paddle1, this->paddle2, this->gameStatus, soundOutput);
    frh = new FrameRateHandler(gameConfig->frameRate);
    gameStatus->status = GameStatus::Status::Stopped;
    strcpy(playerWon, "GAME BEGINS");
    newRound = false;
    stopBall = false;
    nextBallXVelocity = 1;
    lastStoppedBall = 0;

    int nowPlayin = 0;
}

int randomNotZero(int from, int to) {
    int random = rand();
    if(random == 0) return from;
    return (rand() % (to - from)) + from;
}

void Game::restartAndUpdateScores(int player1, int player2) {
    player1Score += player1;
    player2Score += player2;
    ball->setPos_x(board->getMiddleX());
    ball->setPos_y(board->getMiddleY());
    if(player1Score > player2Score) {
        ball->setVelocity_x(1);
        nextBallXVelocity = 1;
    }
    else {
        ball->setVelocity_x(-1);
        nextBallXVelocity = -1;
    }

    ball->setVelocity_y(0);
    gameStatus->status = GameStatus::Status::Running;
    newRound = true;
    stopBall = true;
    lastStoppedBall = millis();
}

void Game::oneFrame() {

    soundOutput->refresh();

    if(gameStatus->status == GameStatus::Status::player1Won) {
        restartAndUpdateScores(1, 0);
        strcpy(playerWon, player1won);
    }

    else if(gameStatus->status == GameStatus::Status::player2Won) {
        restartAndUpdateScores(0, 1);
        strcpy(playerWon, player2won);
    }

    if(!frh->shouldUpdateFrame()) return;

    ((bluetoothInputDevice*)inputDevice2)->print_all();

    //    renderer->clearScreen(Color::Black);

    itoa(player1Score, scoreBuff, 10);
    renderer->drawText(board->getWidth()/2 + 10 - 5, board->getHeight() - 10, scoreBuff);
    itoa(player2Score, scoreBuff, 10);
    renderer->drawText(board->getWidth()/2 - 10 - 5, board->getHeight() - 10, scoreBuff);

    board->update();
    board->render(renderer);

    paddle1->update();
    paddle2->update();

    paddle1->render(renderer);
    paddle2->render(renderer);
    ball->render(renderer);

    if(stopBall) {
        unsigned long millis1 = millis();
        ball->setVelocity_y(0);
        ball->setVelocity_x(0);
        if(millis1 < lastStoppedBall - 1500) lastStoppedBall = millis1;
        if (millis1 < lastStoppedBall + 1500) {
            renderer->drawText(board->getMiddleX() - 25, board->getMiddleY() + 15, playerWon);
        }
        else {
            stopBall = false;
            ball->setVelocity_x(nextBallXVelocity);
        }
    }
    else {
        ball->update();
    }

    if(newRound) {
        newRound = false;
        stopBall = true;
        lastStoppedBall = millis();
    }
    delay(5);
    frh->updatedFrameNow();
}

void Game::start() {
    gameStatus->status = GameStatus::Status::Running;
}

void Game::stop() {
    gameStatus->status = GameStatus::Status::Stopped;
}