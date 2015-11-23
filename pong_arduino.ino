#include "joystickInputDevice.h"
#include "game.h"
#include "arduinoRenderer.h"
#include "randomInputDevice.h"

Game* g;
ArduinoRenderer* ar;
JoystickInputDevice* joy;
randomInputDevice* rid;

void setup() {
  GameConfig gc;

  joy = new JoystickInputDevice(0);

  rid = new randomInputDevice();

  ar = new ArduinoRenderer(120, 96);
  g = new Game(ar, &gc, joy, rid);

  g->start();
}

void loop() {
  g->oneFrame();
}