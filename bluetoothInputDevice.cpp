//
// Created by mihau on 11/24/15.
//

#include "bluetoothInputDevice.h"
#include "memfree.h"

bluetoothInputDevice::bluetoothInputDevice(Renderer* r) {
  print_buf = new char[8]();
//  print_buf2 = new char[10];
  str_size = 0;
  angle = 0;
  last_char = (int)'0';
  debug = r;
}



int bluetoothInputDevice::angleFromBuf() {
  int pipes_saw = 0;
  int res = 0;

  for(int i = 0; str_size > i; i++) {
    if(str_buf[i] == '|')
      pipes_saw++;
    else if(pipes_saw >= 2) {
      str_size = 0;
      return atoi(str_buf + i);
    }
  }
  str_size = 0;
  return -1;
}

//int freeRam ()
//{
//  extern int __heap_start, *__brkval;
//  int v;
//  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
//}

void bluetoothInputDevice::print_all() {
//  itoa(freeRam(), print_buf2, 10);
//  debug->drawText(50, 20, print_buf2);
//  debug->drawText(10, 10, print_buf);
  debug->drawText(30, 30, str_buf);
}

int bluetoothInputDevice::getAngle() {


    while(Serial.available()) {
      int c = Serial.read();
      Serial.write(c);
      if(c == -1) break;
      Serial.write(c);
      if(c == '#') {
        str_buf[str_size] = 0;
        int a = angleFromBuf();
        itoa(a, print_buf, 10);

        if(a != -1) {
          if (a > 150) {
            angle = 255;
          }
          else {
            angle = -255;
          }
          break;
        }
      } else if(c != '*') {
    //    Serial.write('O');
        str_buf[str_size] = c;
        str_size++;
      }
    }


    return angle;
};