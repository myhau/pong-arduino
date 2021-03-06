//
// Created by mihau on 11/10/15.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"


Game::Game(Renderer* renderer, GameConfig* gameConfig, InputDevice* inputDevice1, InputDevice* inputDevice2):
        renderer(renderer),
        player1Score(0), player2Score(0)
{
    gameStatus = new GameStatus;
    board = new Board(gameConfig->boardWidth, gameConfig->boardHeight, 1);
    paddle1 = new Paddle(Paddle::left, gameConfig->paddleWidth, gameConfig->paddleHeight, board, inputDevice1);
    paddle2 = new Paddle(Paddle::right, gameConfig->paddleWidth, gameConfig->paddleHeight, board, inputDevice2);
    ball = new Ball(gameConfig->ballRadius, this->board, this->paddle1, this->paddle2, this->gameStatus);
    frh = new FrameRateHandler(gameConfig->frameRate);
    gameStatus->status = GameStatus::Status::Stopped;
}

int randomNotZero(int from, int to) {
    int random = rand();
    if(random == 0) return from;
    return (rand() % (to - from)) + from;
}

void Game::restartAndUpdateScores(int player1, int player2) {
    player1Score += player1;
    player2Score += player2;
    paddle1->setPos_y(0);
    paddle2->setPos_y(0);
    ball->setPos_x(board->getWidth()/2);
    ball->setPos_y(board->getHeight()/2);
    ball->setVelocity_x(rand() % 4 - 1);
    ball->setVelocity_y(rand() % 3 - 1);
    gameStatus->status = GameStatus::Status::Running;
}

void Game::oneFrame() {
    if(gameStatus->status == GameStatus::Status::player1Won) {
        restartAndUpdateScores(1, 0);
    }

    else if(gameStatus->status == GameStatus::Status::player2Won) {
        restartAndUpdateScores(0, 1);
    }

    if(!frh->shouldUpdateFrame()) return;

    renderer->clearScreen(Color::Black);



    board->update(); board->render(renderer);

    paddle1->update();
    paddle2->update();

    ball->update();


    paddle1->render(renderer);
    paddle2->render(renderer);
    ball->render(renderer);

    frh->updatedFrameNow();

}

void Game::start() {
    gameStatus->status = GameStatus::Status::Running;
}

void Game::stop() {
    gameStatus->status = GameStatus::Status::Stopped;
}