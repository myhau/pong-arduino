#include <SFML/Graphics.hpp>

#include <unistd.h>
#include <iostream>

typedef int uint8_t;

using namespace sf;

#define INVERT 1
#define WHITE 2

class MyTv {
private:
    uint8_t w;
    uint8_t h;
    RenderWindow window;
    uint8_t joystick_state;


public:
    MyTv(uint8_t w, uint8_t h): window(VideoMode(w, h), "My window") {
        this->w = w;
        this->h = h;



    }

    void update_all() {
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
                    joystick_state = 0;
                    for (int i = 0; i < n; i++) {
                        if (k[i] == event.key.code) {
                            joystick_state = (uint8_t) ((double) (i + 1) * ((double) max_joy_state / (double) n));
                        }
                    }
                }
            }

            // clear the window with black color
            window.clear(sf::Color::Black);

            // draw everything here...

            // end the current frame
            window.display();
        }
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
                    joystick_state = 0;
                    for (int i = 0; i < n; i++) {
                        if (k[i] == event.key.code) {
                            joystick_state = (uint8_t) ((double) (i + 1) * ((double) max_joy_state / (double) n));
                        }
                    }

                }
            }

            // clear the window with black color
//            window.clear(sf::Color::Black);
        }
    }

    void draw_window() {
        if(window.isOpen()) window.display();
    }

    void draw_rect(uint8_t x0, uint8_t y0, uint8_t w1, uint8_t h1, char c1) {
        draw_rect(x0, y0, w1, h1, c1, 123);
    }


    void draw_rect(uint8_t x0, uint8_t y0, uint8_t w1, uint8_t h1, char c1, char invert) {
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
    void draw_circle(uint8_t x, uint8_t y, uint8_t r, char c1, char c2) {
        check_and_clear();
        CircleShape cs(r, 10);
        cs.setPosition(x, y);
        cs.setFillColor(Color::White);
        window.draw(cs);
        draw_window();
    };
    void clear_screen() {
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

    uint8_t get_joystick_state() {
        return joystick_state;
    }

};

//uint8_t width = 120;
//uint8_t height = 96;

uint8_t width = 800;
uint8_t height = 600;

MyTv TV(width, height);



void setup() {
}



void drawPaletka1(int y1) {
    TV.draw_rect(0, y1, 10, 30,WHITE, INVERT);
}

void drawPaletka2(int y1) {
    TV.draw_rect(width - 10, y1, 10, 30,WHITE, INVERT);
}

void drawPilka(int x1, int y1) {
    TV.draw_circle(x1, y1, 5, WHITE,INVERT);
}

void drawPlansza() {
    TV.draw_rect(0, 0, width - 1, height - 1, WHITE);
}

int velocityY1 = 1;
int y11 = 0;

int velocityY2 = 2;
int y2 = 0;

int velocityPx = 1;
int velocityPy = 1;

int pX = 20;

int pY = 30;

void delay(unsigned int mili) {
    sf::sleep(sf::milliseconds(mili));
}

void draw_cube() {
    using namespace std;
    TV.clear_screen();
    cout << "HEHE" << endl;
    drawPlansza();
    y11 += velocityY1;
    y2 += velocityY2;

    pX += velocityPx;
    pY += velocityPy;

    if(y11 + 30 >= height) velocityY1 = -1;
    if(y11 <= 0) velocityY1 = 1;

    if(y2 + 30 >= width) velocityY2 = -1;
    if(y2 <= 0) velocityY2 = 1;


    if(pX + 5 >= width) velocityPx = -1;
    if(pX <= 1) velocityPx = 1;

    if(pY + 5 >= height) velocityPy = -1;
    if(pY <= 1) velocityPy = 1;
    drawPaletka1(y11);
    drawPaletka2(y2);
    drawPilka(pX, pY);

    delay(10);

}

void loop() {
    draw_cube();
}

int main() {
    while(1) {
        delay(1);
        loop();
    }


   return 0;
}