//
// Created by mihau on 11/24/15.
//

#ifndef PONG_ARDUINO_MOCK_BLUETOOTHINPUTDEVICE_H
#define PONG_ARDUINO_MOCK_BLUETOOTHINPUTDEVICE_H
#include "inputDevice.h"
#include "Arduino.h"

class bluetoothInputDevice : public InputDevice {
private:
    int angle;
    int last_char;
public:
    bluetoothInputDevice();
    int getAngle() override ;
};


#endif //PONG_ARDUINO_MOCK_BLUETOOTHINPUTDEVICE_H
