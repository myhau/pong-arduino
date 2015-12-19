//
// Created by mihau on 11/24/15.
//

#ifndef PONG_ARDUINO_MOCK_BLUETOOTHINPUTDEVICE_H
#define PONG_ARDUINO_MOCK_BLUETOOTHINPUTDEVICE_H
#include "inputDevice.h"
#include "Arduino.h"
#include "renderer.h"

class bluetoothInputDevice : public InputDevice {
private:
    int angle;
    int last_char;
    char str_buf[8];
    int str_size;
    int angleFromBuf();
    Renderer* debug;
    char* print_buf;
    char* print_buf2;
public:
    bluetoothInputDevice(Renderer*);
    void print_all();
    int getAngle() override ;
};


#endif //PONG_ARDUINO_MOCK_BLUETOOTHINPUTDEVICE_H
