#include "soundOutput.h"
#include "Arduino.h"

SoundOutput::SoundOutput() {
    playingNow = nullptr;
    this->queueFirst = 0;
    this->queueLast = 0;
}

void Sound::buzz() {}

void Sound::stop() {}

unsigned long Silence::getForMs() {
    return this->forMs;
}

Silence::Silence(unsigned long forMs) {
    this->forMs = forMs;
}

BuzzSound::BuzzSound(int pin, int howLoud, unsigned long forMs) {
    this->pin = pin;
    this->howLoud = howLoud;
    this->forMs;
    pinMode(pin, OUTPUT);
}

void BuzzSound::buzz() {
    digitalWrite(this->pin, 1);
}
void BuzzSound::stop() {
    digitalWrite(this->pin, 0);
}

unsigned long BuzzSound::getForMs() {
    return this->forMs;
}

void SoundOutput::scheduleSound(Sound* sound) {
    // round buffer q
    this->buzzQueue[queueLast] = sound;
    if(queueFirst > queueLast) {
        if(queueFirst - queueLast == 1) {
            queueFirst = (queueFirst + 1) % SoundOutput::QUEUE_MAX;
        }
        queueLast = (queueLast + 1) % SoundOutput::QUEUE_MAX;
    } else if(queueFirst == queueLast) {
        queueLast++;
    }
    else {
        queueLast = (queueLast + 1) % SoundOutput::QUEUE_MAX;
    }
}

void SoundOutput::refresh() {
    unsigned long now = millis();
    if(playingNow == nullptr) {
        // if q empty
        if(queueLast == queueFirst) return;
        playingNow = buzzQueue[queueFirst];
        queueFirst = (queueFirst + 1) % SoundOutput::QUEUE_MAX;
        startedBuzzingThis = now;
        playingNow->buzz();
    }
    else if(startedBuzzingThis > now || now > startedBuzzingThis + playingNow->getForMs()) {
        playingNow->stop();
        playingNow = nullptr;
    }
}