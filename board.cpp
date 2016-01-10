//
// Created by mihau on 11/10/15.
//

#include "board.h"


Board::Board(int width, int height, int thickness):
        w(width), h(height), thickness(thickness) {

}

int Board::getWidth() const {
    return w;
}

int Board::getHeight() const {
    return h;
}

int Board::getMiddleY() const {
    return this->getHeight()/2;
}

int Board::getMiddleX() const {
    return this->getWidth()/2;
}


void Board::update() {
}

void Board::render(Renderer* r) {
    r->drawRect(1, 1, w, h, Color::White);
}

