#include <SFML/Graphics.hpp>

#include <unistd.h>
#include <iostream>
#include <ctime>
#include <sys/time.h>

typedef int uint8_t;

using namespace sf;

#define INVERT 1
#define WHITE 2


int width = 800;
int height = 640;

int velocityY1 = 1;
int y11 = 0;

int velocityY2 = 2;
int y2 = 0;

int velocityPx = 1;
int velocityPy = 1;

int px = (width/2);

int py = (height/2);

int player1Score = 0;
int player2Score = 0;

int start = 1;

virtual class InputDevice {
public:
//    InputDevice() {}
    virtual uint8_t getAngle()  = 0;
};

class JoystickInputDevice: InputDevice {

};

class MockInputDevice: InputDevice {
private:
    uint8_t angle;

public:
    MockInputDevice(): angle(0) {

    }
    uint8_t getAngle() override {

    }
    void setAngle(uint8_t angle) {
        this->angle = angle;
    }
};

class BluetoothInputDevice: InputDevice {

};


virtual class Renderer {
public:
    virtual void drawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, Color c, bool filled = false) = 0;
    virtual void drawCircle(uint8_t x, uint8_t y, uint8_t radius, Color c, bool filled = false) = 0;
    virtual void clearScreen(Color c) = 0;
    virtual uint8_t screenWidth() = 0;
    virtual uint8_t screenHeight() = 0
};

class DesktopRenderer: public Renderer {
private:
    uint8_t w;
    uint8_t h;
    RenderWindow window;
    MockInputDevice mockInputDevice;

public:
    DesktopRenderer(uint8_t w, uint8_t h): window(VideoMode(w, h), "My window"), mockInputDevice() {
        this->w = w;
        this->h = h;
    }

    InputDevice* getInputDevice() {
        return (InputDevice*)&mockInputDevice;
    }

    uint8_t screenWidth() {
        return this->w;
    }
    uint8_t screenHeight() {
        return this->h;
    }

    void check_and_clear() {
        std::cout << "HEHE" << std::endl;
        if(window.isOpen()) {

            Event event;
            while (window.pollEvent(event)) {
                // "close requested" event: we close the window
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::KeyPressed) {
                    const int n = 9;
                    const int max_joy_state = 1024;
                    Keyboard::Key k[] =
                            {Keyboard::A, Keyboard::S, Keyboard::D, Keyboard::F,
                             Keyboard::G, Keyboard::H, Keyboard::J, Keyboard::K, Keyboard::L};
                    uint8_t joystick_state = 0;
                    for (int i = 0; i < n; i++) {
                        if (k[i] == event.key.code) {
                            joystick_state = (uint8_t) ((double) (i + 1) * ((double) max_joy_state / (double) n));
                        }
                    }
                    mockInputDevice.setAngle(joystick_state);

                }
            }

            // clear the window with black color
//            window.clear(sf::Color::Black);
        }
    }

    void draw_window() {
        if(window.isOpen()) window.display();
    }

    void drawRect(uint8_t x0, uint8_t y0, uint8_t w1, uint8_t h1, char c1) {
        drawRect(x0, y0, w1, h1, c1, 123);
    }


    void drawRect(uint8_t x0, uint8_t y0, uint8_t w1, uint8_t h1, char c1, char invert) {
        check_and_clear();
        RectangleShape rs;
        rs.setSize(Vector2f(w1, h1));
        rs.setPosition(x0, y0);
        if(invert == INVERT) {
            rs.setFillColor(Color::White);
            rs.setOutlineColor(Color::Black);
        }
        if(invert != INVERT) {
            rs.setFillColor(Color::Black);
            rs.setOutlineColor(Color::White);
        }

        rs.setOutlineThickness(1);

        window.draw(rs);
        draw_window();
    }
    void drawCircle(uint8_t x, uint8_t y, uint8_t r, char c1, char c2) {
        check_and_clear();
        CircleShape cs(r, 10);
        cs.setPosition(x, y);
        cs.setFillColor(Color::White);
        window.draw(cs);
        draw_window();
    };
    void clearScreen() {
        check_and_clear();
//        window./
        RectangleShape clearRect;
        clearRect.setSize(Vector2f(this->w, this->h));
        std::cout << this->w << std::endl;
        clearRect.setPosition(0, 0);
        clearRect.setFillColor(sf::Color::Black);
        window.draw(clearRect);
        draw_window();
    };

    void draw_it() {
        draw_window();
    }

    void delay_frame(uint8_t x) {

    }
};

class ArduinoRenderer: Renderer {

};

virtual class GameObject {
    virtual void update() = 0;
    virtual void render(Renderer* r) = 0;
};

class Ball: GameObject {

private:
    uint8_t radius;
    int8_t velocity_x;
    int8_t velocity_y;
    uint8_t pos_x;
    uint8_t pos_y;
    Board* board;
    Paddle* paddle1;
    Paddle* paddle2;


    bool didCollide(Paddle* p) {
        bool isLeftPaddle = p->getWhichPaddle() == Paddle::left;
        bool collided = false;
        collided |=
                (isLeftPaddle && p->getPosX() + p->getWidth() >= pos_x - radius)
                | (isLeftPaddle && p->getPosX() - p->getWidth() >= pos_x + radius);
        collided |= pos_x > p->getPosY() && (p->getPosY() + p->getHeight()) > pos_x;
        return collided;
    }

    bool didCollide(Board* b) {
        bool collided = false;
        collided |= pos_x - radius <= 0;
        collided |= pos_x + radius >= b->getWidth();
        collided |= pos_y - radius <= 0;
        collided |= pos_y + radius >= b->getHeight();
        return collided;
    }

    void handleCollision(Paddle* p) {
        velocity_x = -velocity_x;
        velocity_y += p->getVelocityY(); // TODO: change :D
    }
    void handleCollision(Board* b) {
        if(pos_x - radius <= 0 | pos_y + radius >= b->getHeight()) velocity_x = -velocity_x;
        if(pos_y - radius <= 0 | pos_x + radius >= b->getWidth()) velocity_y = -velocity_y;
    }


public:
    Ball(uint8_t radius, Board* b, Paddle* paddle1, Paddle* paddle2):
            board(b), paddle1(paddle1), paddle2(paddle2),
            radius(radius), velocity_x(0), velocity_y(0), pos_x(0), pos_y(0) {
    }
    Ball(uint8_t radius, uint8_t initial_pos_x, uint8_t initial_pos_y, Board* b, Paddle* paddle1, Paddle* paddle2):
            Ball(radius, b, paddle1, paddle2), pos_x(initial_pos_x), pos_y(initial_pos_y) {}

    void update() {
        if(didCollide(paddle1))
            handleCollision(paddle1);
        else if(didCollide(paddle2))
            handleCollision(paddle2);
        else if(didCollide(board))
            handleCollision(board);

        pos_x += velocity_x;
        pos_y += velocity_y;

    }
    void render(Renderer* r) {
        r->drawCircle(pos_x, pos_y, radius, Color::White, true);
    }

};

class Board: GameObject {
private:
    uint8_t w;
    uint8_t h;
    uint8_t thickness;
public:
    Board(uint8_t width, uint8_t height, uint8_t thickness):
            w(width), h(height), thickness(thickness) {
    }


    uint8_t getWidth() const {
        return w;
    }

    uint8_t getHeight() const {
        return h;
    }

    void update() {
    }

    void render(Renderer* r) {
        r->drawRect(0, 0, w, h, Color::White);
    }

};

class Paddle: GameObject {
private:
    Which which_paddle;
    uint8_t w;
    uint8_t h;
    uint8_t velocity_y;
    uint8_t pos_y;
    uint8_t pos_x;
    Board* board;
    InputDevice* device;
public:
    typedef char Which;
    static Which left = 0;
    static Which right = 1;

    Paddle(Paddle::Which which, uint8_t paddle_width, uint8_t paddle_height, Board* b, InputDevice* device1):
            device(device1), board(b), which_paddle(which), w(paddle_width), h(paddle_height), velocity_y(0), pos_y(0) {
        pos_x = (which_paddle == left) ? (uint8_t)0 : board->getWidth() - w;
    }


    uint8_t getVelocityY() const {
        return velocity_y;
    }

    uint8_t getWidth() const {
        return w;
    }

    uint8_t getHeight() const {
        return h;
    }

    uint8_t getPosY() const {
        return pos_y;
    }

    uint8_t getPosX() const {
        return pos_x;
    }

    Which getWhichPaddle() const {
        return which_paddle;
    }

    void update() {
        velocity_y = device->getAngle()/(uint8_t)200;
        pos_y += velocity_y;
        if(pos_y + h > board->getWidth())
            pos_y = board->getWidth() - h;
        else if(pos_y < 0) pos_y = 0;
    }
    void render(Renderer* r) {
        r->drawRect(pos_x, pos_y, w, h, Color::White, true);
    }
};

struct GameConfig {
    uint8_t ballRadius = 5;
    uint8_t paddleHeight = 5;
    uint8_t paddleWidth = 50;
    uint8_t boardWidth = 120;
    uint8_t boardHeight = 96;
    uint8_t frameRate = 30;
};

class FrameRateHandler {
private:
    uint8_t frameRate;
    long lastUpdate;
    long shouldUpdateEvery;

    long int nowInUs() {
        struct timeval tp;
        gettimeofday(&tp, NULL);
        long int ms = tp.tv_sec * 1000000 + tp.tv_usec;
        return ms;
    }
public:
    FrameRateHandler(uint8_t frameRate):
            frameRate(frameRate),
            lastUpdate(0),
            shouldUpdateEvery(1000000 / frameRate)
    { }
    void updatedFrameNow() {
        lastUpdate = nowInUs();
    }
    bool shouldUpdateFrame() {
        return nowInUs() - lastUpdate > shouldUpdateEvery;
    }
};

class Game {
private:
    Board board;
    Ball ball;
    Paddle paddle1;
    Paddle paddle2;
    Renderer* renderer;
    FrameRateHandler frh;
public:
    Game(Renderer* renderer, GameConfig* gameConfig, InputDevice* inputDevice):     
            board(gameConfig->boardWidth, gameConfig->boardHeight, 1),
            paddle1(Paddle::left, gameConfig->paddleWidth, gameConfig->paddleHeight, &board, inputDevice),
            paddle2(Paddle::right, gameConfig->paddleWidth, gameConfig->paddleHeight, &board, inputDevice),
            ball(gameConfig->ballRadius, &board, &paddle1, &paddle2),
            frh(gameConfig->frameRate)
    {

    }

    void oneFrame() {
        if(!frh.shouldUpdateFrame()) return;

        renderer->clearScreen(Color::Black);

        board.update(); board.render(renderer);
        paddle1.update();
        paddle2.update();
        ball.update();
        
        paddle1.render(renderer);
        paddle2.render(renderer);
        ball.render(renderer);

        frh.updatedFrameNow();
    }

    void start() {

    }
};



//MyTv TV(width, height);
//
//
//bool powerToTheBall(int paddle){
//    if(paddle==1){
//        return ((y11 > 0 && py > 0) || (y11 <= 0 && py <= 0));
//    }else{
//        return ((y2 > 0 && py >0)||(y2<=0 && py <= 0));
//    }
//}
//
//int random(int from, int to) {
//    return 1;
//}
//
//void drawBall() {
//
//    if(px + 6 >= width) {
//        start = random(0,1);
//        if(start==0){
//            velocityPx = -1;
//            velocityPy = 0;
//        }else{
//            velocityPx = 1;
//            velocityPy = 0;
//        }
//        player1Score++;
//        px = (width/2);
//        py = (height/2);
//    }
//
//    if(px - 5 <= 1){
//        if(start==0){
//            velocityPx = -1;
//            velocityPy = 0;
//        }else{
//            velocityPx = 1;
//            velocityPy = 0;
//        }
//        player2Score++;
//        px = (width/2);
//        py = (height/2);
//    }
//
//    if(py + 6 >= height) velocityPy = -1;
//    if(py - 5 <= 1) velocityPy = 1;
//
//    if((px + 5  >= width -10) && (y11 >= py && y11 <= py + 30)){
//        velocityPx = -velocityPx;
//        if(powerToTheBall(2)){
//            velocityPy += 0.1;
//        }else{
//            velocityPy -= 0.1;
//        }
//    }
//
//    if((px - 5  <= 0) && (y11 >= py && y11 <= py + 30)){
//        velocityPx = -velocityPx;
//        if(powerToTheBall(1)){
//            velocityPy += 0.1;
//        }else{
//            velocityPy -= 0.1;
//        }
//    }
//    TV.draw_circle(px, py, 5, WHITE,INVERT);
//}
//
//
//void drawBoard() {
//    TV.draw_rect(0, 0, width - 1, height - 1, WHITE);
//}
//
//
//void drawPaddle1(int y1) {
//    if(y1 + 30 >= height) velocityY1 = -1;
//    if(y1 <= 0) velocityY1 = 1;
//    TV.draw_rect(0, y1, 10, 30,WHITE, INVERT);
//}
//
//void drawPaddle2(int y1) {
//    if (y2 + 30 >= height) velocityY2 = -1;
//    if (y2 <= 0) velocityY2 = 1;
//    TV.draw_rect(width - 10, y1, 10, 30, WHITE, INVERT);
//
//}
//
//void delay(uint8_t mili) {
//    sf::sleep(sf::milliseconds(mili));
//}
//
//void draw_pong() {
//    y11 += velocityY1;
//    y2 += velocityY2;
//
//    px += velocityPx;
//    py += velocityPy;
//
//
//    drawPaddle1(y11);
//    drawPaddle2(y2);
//    drawBall();
//
//    delay(1);
//}
//
//
//void start_game() {
//    TV.delay_frame(1);
//    TV.clear_screen();
//    drawBoard();
//    draw_pong();
//}

Game* game;
GameConfig gameConfig;
DesktopRenderer* desktopRenderer;

void setup() {
    desktopRenderer = new DesktopRenderer(gameConfig.boardWidth, gameConfig.boardHeight);
    InputDevice* iDevice = desktopRenderer->getInputDevice();
    game = new Game(desktopRenderer, &gameConfig, iDevice);
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
