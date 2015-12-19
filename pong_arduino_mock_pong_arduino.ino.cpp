// automatically generated by arduino-cmake
#line 1 "/home/mihau/workspace/pong-arduino-mock/pong_arduino.ino"
#include "joystickInputDevice.h"
#include "game.h"
#include "arduinoRenderer.h"
#include "randomInputDevice.h"
#include "mockInputDevice.h"
#include "bluetoothInputDevice.h"
#line 10 "/home/mihau/workspace/pong-arduino-mock/pong_arduino_mock_pong_arduino.ino.cpp"
#include "Arduino.h"

//=== START Forward: /home/mihau/workspace/pong-arduino-mock/pong_arduino.ino
 void setup() ;
 void setup() ;
 void loop() ;
 void loop() ;
//=== END Forward: /home/mihau/workspace/pong-arduino-mock/pong_arduino.ino
#line 5 "/home/mihau/workspace/pong-arduino-mock/pong_arduino.ino"


Game* g;
ArduinoRenderer* ar;
JoystickInputDevice* joy;
InputDevice* rid;
TVout* TV;

void setup() {
  GameConfig gc;

  joy = new JoystickInputDevice(0);




  ar = new ArduinoRenderer(120, 96);
  rid = new bluetoothInputDevice(ar);
  g = new Game(ar, &gc, joy, rid);

  TV = &(ar->TV);

  Serial.begin(9600);



  g->start();
}

void loop() {
  TV->delay_frame(1);
  TV->clear_screen();
  g->oneFrame();
}
