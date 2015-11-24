//
// Created by mihau on 11/10/15.
//

#ifdef ARDUINO

#else
#include <iostream>
#endif
#include "ball.h"


void Ball::setVelocity_x(float velocity_x) {
    this->velocity_x = velocity_x;
}

void Ball::setVelocity_y(float velocity_y) {
    this->velocity_y = velocity_y;
}

void Ball::setPos_x(float pos_x) {
    this->pos_x = pos_x;
}

void Ball::setPos_y(float pos_y) {
    this->pos_y = pos_y;
}

bool Ball::didCollide(Board* b) {
    bool collided = false;
    collided |= pos_x - radius < 0;
    collided |= pos_x + radius > b->getWidth();
    collided |= pos_y - radius < 0;
    collided |= pos_y + radius > b->getHeight();
    if(collided) {
        #ifndef ARDUINO
        std::cout << "collided with board " << std::endl;
        #endif
    }
    return collided;
}

bool Ball::didCollide(Paddle* p) {
    bool isLeftPaddle = p->getWhichPaddle() == Paddle::left;
    bool collided;
    collided =
            (isLeftPaddle && (p->getPosX() + p->getWidth() > pos_x - radius))
            | (!isLeftPaddle && (p->getPosX() < pos_x + radius));
    collided &= (pos_y > p->getPosY()) && ((p->getPosY() + p->getHeight()) > pos_y);
    return collided;
}

void Ball::handleCollision(Paddle* p) {
    #ifndef ARDUINO
    std::cout << "collided with paddle " << ((p->getWhichPaddle() == Paddle::left) ? 0 : 1) << std::endl;
    #endif
    velocity_x = -velocity_x;
    velocity_y += p->getVelocityY()/4.0;
    if(velocity_y > 5) {
        velocity_y = 5;
    };
}

void Ball::handleCollision(Board* b) {
    if(pos_y - radius < 0) {
        velocity_y = -velocity_y;
        pos_y = radius;
    }
    else if(pos_y + radius > b->getHeight()) {
        velocity_y = -velocity_y;
        pos_y = b->getHeight() - radius + velocity_y ;
    }
    else if(pos_x - radius < 0) {
        gameStatus->status = GameStatus::Status::player1Won;
    }
    else if(pos_x + radius > b->getWidth()) {
        gameStatus->status = GameStatus::Status::player2Won;
    }
}

Ball::Ball(float radius, Board* b, Paddle* paddle1, Paddle* paddle2, GameStatus* g):
        board(b), paddle1(paddle1), paddle2(paddle2),
        radius(radius), velocity_x(-1), velocity_y(rand() % 2 - 0.5),
        pos_x(b->getWidth()/2), pos_y(b->getHeight()/2), gameStatus(g) {
}

Ball::Ball(float radius, float initial_pos_x, float initial_pos_y, Board* b, Paddle* paddle1, Paddle* paddle2, GameStatus* g):
        Ball(radius, b, paddle1, paddle2, g) {
    pos_x = initial_pos_x; pos_y = initial_pos_y;
}

void Ball::update() {
    if(didCollide(paddle1))
        handleCollision(paddle1);
    else if(didCollide(paddle2))
        handleCollision(paddle2);
    else if(didCollide(board))
        handleCollision(board);

    pos_x += velocity_x;
    pos_y += velocity_y;


}
void Ball::render(Renderer* r) {
    r->drawCircle(pos_x, pos_y, radius, Color::White, true);
}

