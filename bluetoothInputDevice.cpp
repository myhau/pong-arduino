//
// Created by mihau on 11/24/15.
//

#include "bluetoothInputDevice.h"

bluetoothInputDevice::bluetoothInputDevice() {
    angle = 0;
    last_char = (int)'0';
}

char str_buf[30];
int str_size;

int angleFromBuf() {
  int pipes_saw = 0;

  for(int i = 0; str_size > i; i++) {
    if(str_buf[i] == '|')
      pipes_saw++;
    else if(pipes_saw >= 2) {
      return atoi(str_buf + i - 1);
    }
  }
  str_size = 0;
}

int bluetoothInputDevice::getAngle() {

    while(Serial.available()) {
      int c = Serial.read();
      if(c == -1) break;
    //  Serial.write(c);

      if(c == '#') {
        angle = angleFromBuf();
      } else if(c != '*') {
    //    Serial.write('O');
        str_buf[str_size] = c;
        str_size++;
      }
    }

    return angle;
};
