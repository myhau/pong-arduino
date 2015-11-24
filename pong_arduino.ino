#include "joystickInputDevice.h"
#include "game.h"
#include "arduinoRenderer.h"
#include "randomInputDevice.h"
#include "mockInputDevice.h"
Game* g;
ArduinoRenderer* ar;
JoystickInputDevice* joy;
InputDevice* rid;
TVout* TV;

void setup() {
  GameConfig gc;

  joy = new JoystickInputDevice(0);

  rid = new randomInputDevice();


  ar = new ArduinoRenderer(120, 96);
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