//
// Created by mihau on 11/10/15.
//

// #include <iostream>
#include "game.h"
#include "bluetoothInputDevice.h"
#include "string.h"

#ifdef ARDUINO
int rand() {
    return random(10000000);
}
#endif

Game::Game(Renderer* renderer, GameConfig* gameConfig, InputDevice* inputDevice1, InputDevice* inputDevice2):
        renderer(renderer),
        player1Score(0), player2Score(0)
{
    this->inputDevice2 = inputDevice2;
    gameStatus = new GameStatus;
    board = new Board(gameConfig->boardWidth - 3, gameConfig->boardHeight - 3, 1);
    paddle1 = new Paddle(Paddle::left, gameConfig->paddleWidth, gameConfig->paddleHeight, board, inputDevice1);
    paddle2 = new Paddle(Paddle::right, gameConfig->paddleWidth, gameConfig->paddleHeight, board, inputDevice2);
    ball = new Ball(gameConfig->ballRadius, this->board, this->paddle1, this->paddle2, this->gameStatus);
    frh = new FrameRateHandler(gameConfig->frameRate);
    gameStatus->status = GameStatus::Status::Stopped;
    newRound = false;
    stopBall = false;
    long lastStoppedBall = 0;
}

int randomNotZero(int from, int to) {
    int random = rand();
    if(random == 0) return from;
    return (rand() % (to - from)) + from;
}

void Game::restartAndUpdateScores(int player1, int player2) {
    player1Score += player1;
    player2Score += player2;
//    paddle1->setPos_y(0);
//    paddle2->setPos_y(0);
    ball->setPos_x(board->getWidth()/2);
    ball->setPos_y(board->getHeight()/2);
    if(player1Score > player2Score) {
        ball->setVelocity_x(1);
    }
    else {
        ball->setVelocity_x(-1);
    }
    ball->setVelocity_y(0);
    gameStatus->status = GameStatus::Status::Running;
    newRound = true;
}

void Game::oneFrame() {
    if(gameStatus->status == GameStatus::Status::player1Won) {
        restartAndUpdateScores(1, 0);
//        strcpy(scoreBuff, "Player 1 won !");
    }

    else if(gameStatus->status == GameStatus::Status::player2Won) {
        restartAndUpdateScores(0, 1);
//        strcpy(scoreBuff, "Player 2 won !");
    }

    if(!frh->shouldUpdateFrame()) return;



//    renderer->clearScreen(Color::Black);

    ((bluetoothInputDevice*)inputDevice2)->print_all();


    itoa(player1Score, scoreBuff, 10);
    renderer->drawText(board->getWidth()/2 + 10 - 5, board->getHeight() - 10, scoreBuff);
    itoa(player2Score, scoreBuff, 10);
    renderer->drawText(board->getWidth()/2 - 10 - 5, board->getHeight() - 10, scoreBuff);

    board->update(); board->render(renderer);

    paddle1->update();
    paddle2->update();

    ball->update();

//    if(stopBall && (millis() - 3000 < lastStoppedBall)) {
//        ball->setPos_x(0);
//        ball->setPos_y(0);
////        renderer->drawText(50, 50, "DUPA1");
//    }
//    else {
////        renderer->drawText(50, 50, "DUPA2");
//        stopBall = false;
//
//    }

//    itoa(lastStoppedBall, scoreBuff, 10);
//    renderer->drawText(30, 50, scoreBuff);
//
//    itoa(millis(), scoreBuff, 10);
//    renderer->drawText(30, 30, scoreBuff);

    paddle1->render(renderer);
    paddle2->render(renderer);
    ball->render(renderer);






    if(newRound) {
//        renderer->drawText(board->getWidth()/2 - 20, board->getHeight()/2, (char*)player1won);
        newRound = false;
        stopBall = true;
        lastStoppedBall = millis();
    }
    delay(1);
    frh->updatedFrameNow();


}

void Game::start() {
    gameStatus->status = GameStatus::Status::Running;
}

void Game::stop() {
    gameStatus->status = GameStatus::Status::Stopped;
}