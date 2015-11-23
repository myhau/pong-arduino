//
// Created by mihau on 11/10/15.
//

#ifndef PONG_ARDUINO_MOCK_GAMESTATUS_H
#define PONG_ARDUINO_MOCK_GAMESTATUS_H


class GameStatus {
public:
    class Status { 
    public:
      static int player1Won;
      static int player2Won;
      static int Stopped;
      static int Running;
    };
    int status;
};

#endif //PONG_ARDUINO_MOCK_GAMESTATUS_H
