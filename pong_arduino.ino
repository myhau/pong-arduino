#include "joystickInputDevice.h"
#include "game.h"
#include "arduinoRenderer.h"
#include "randomInputDevice.h"
#include "mockInputDevice.h"
#include "bluetoothInputDevice.h"
#include "memfree.h"

Game *g;
ArduinoRenderer *ar;
JoystickInputDevice *joy;
InputDevice *rid;
TVout *TV;

bool first_time = true;

void setup() {
    GameConfig gc;

    joy = new JoystickInputDevice(0);
    ar = new ArduinoRenderer(gc.boardWidth + 10, gc.boardHeight + 8);
    rid = new bluetoothInputDevice(ar);
    g = new Game(ar, &gc, joy, rid);

    TV = &(ar->TV);

    Serial.begin(9600);

    g->start();
}

void loop() {
    TV->delay_frame(1);
    TV->clear_screen();
    if (first_time) {
        first_time = false;
        delay(5000);
    }
    g->oneFrame();
}
