//
// Created by mihau on 11/10/15.
//

#ifndef PONG_ARDUINO_MOCK_FRAMERATE_H
#define PONG_ARDUINO_MOCK_FRAMERATE_H

class FrameRateHandler {
private:
    float frameRate;
    long lastUpdate;
    long shouldUpdateEvery;


public:
    FrameRateHandler(int frameRate);
    void updatedFrameNow();
    bool shouldUpdateFrame();
    long int nowInUs();
};

#endif //PONG_ARDUINO_MOCK_FRAMERATE_H


