
#include <cmath>
#include <iostream>

#include "desktopRenderer.h"
#include "game.h"
#include "gameConfig.h"
#include "mockInputDevice.h"
#include "inputDevice.h"


Game* game;
GameConfig gameConfig;
DesktopRenderer* desktopRenderer;
MockInputDevice* iDevice2;
void setup() {
    desktopRenderer = new DesktopRenderer(ceil(gameConfig.boardWidth), ceil(gameConfig.boardHeight));
    InputDevice* iDevice = desktopRenderer->getInputDevice();
    iDevice2 = new MockInputDevice;
    iDevice2->setAngle(0);

    game = new Game(desktopRenderer, &gameConfig, iDevice, iDevice2);
    game->start();
}

void loop() {
    game->oneFrame();
}

int main() {
    setup();
    while(true) {
        loop();
    }
    return 0;
}
