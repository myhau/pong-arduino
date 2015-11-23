//
// Created by mihau on 11/10/15.
//

#ifndef PONG_ARDUINO_MOCK_GAMESTATUS_H
#define PONG_ARDUINO_MOCK_GAMESTATUS_H


class GameStatus {
public:
    enum Status { player1Won, player2Won, Stopped, Running };
    Status status;
};

#endif //PONG_ARDUINO_MOCK_GAMESTATUS_H
