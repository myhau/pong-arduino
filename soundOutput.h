//
// Created by mihau on 1/12/16.
//

#ifndef PONG_ARDUINO_MOCK_SOUNDOUTPUT_H
#define PONG_ARDUINO_MOCK_SOUNDOUTPUT_H

class Sound {
public:
    virtual void buzz();
    virtual void stop();
    virtual unsigned long getForMs();
};

class Silence: public Sound {
private:
    unsigned long forMs;
public:
    Silence(unsigned long forMs);
    unsigned long getForMs();
};

class BuzzSound: public Sound {
private:
    int howLoud;
    int pin;
    unsigned long forMs;
public:
    void buzz() override;
    void stop() override;
    unsigned long getForMs();
    BuzzSound(int pin, int howLoud, unsigned long forMs);
};

class SoundOutput {
private:
    Sound* playingNow;
    int startedBuzzingThis;
    const static int QUEUE_MAX = 32;
    Sound* buzzQueue[SoundOutput::QUEUE_MAX];
    int queueFirst;
    int queueLast;
public:
    SoundOutput();
    void scheduleSound(Sound* sound);
    void refresh();
};


#endif //PONG_ARDUINO_MOCK_SOUNDOUTPUT_H

