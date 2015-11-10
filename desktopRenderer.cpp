//
// Created by mihau on 11/10/15.
//

#include "desktopRenderer.h"


DesktopRenderer::DesktopRenderer(int w, int h): window(sf::VideoMode(w, h), "My window"), mockInputDevice() {
        this->w = w;
        this->h = h;
    }

    InputDevice* DesktopRenderer::getInputDevice() {
        return (InputDevice*)&mockInputDevice;
    }

    int DesktopRenderer::screenWidth() {
        return this->w;
    }
    int DesktopRenderer::screenHeight() {
        return this->h;
    }

    void DesktopRenderer::check_and_clear() {
        using namespace sf;
        if(window.isOpen()) {

            Event event;
            while (window.pollEvent(event)) {
                // "close requested" event: we close the window
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::KeyPressed) {
                    const int n = 9;
                    const int joy_states = 1024;
                    const int min_joy_state = -512;
                    const int max_joy_state = 512;
                    sf::Keyboard::Key k[] =
                            {Keyboard::A, Keyboard::S, Keyboard::D, Keyboard::F,
                             Keyboard::G, Keyboard::H, Keyboard::J, Keyboard::K, Keyboard::L};
                    int joystick_state = 0;
                    for (int i = 0; i < n; i++) {
                        if (k[i] == event.key.code) {
                            joystick_state = (int) ((double) (i + 1) * ((double) joy_states / (double) n));
                        }
                    }
                    joystick_state += min_joy_state;
                    mockInputDevice.setAngle(joystick_state);

                }
            }
        }
    }

    void DesktopRenderer::draw_window() {
        if(window.isOpen()) window.display();
    }

    void DesktopRenderer::drawRect(int x0, int y0, int w1, int h1, Color c, bool filled) {
        sf::Color c2 = c == Color::White ? sf::Color::White : sf::Color::Black;
        check_and_clear();
        sf::RectangleShape rs;
        rs.setSize(sf::Vector2f(w1, h1));
        rs.setPosition(x0, y0);
        rs.setOutlineColor(c2);
        if(filled) {
            rs.setFillColor(c2);
        }
        else rs.setFillColor(sf::Color(sf::Color(255, 255, 255).toInteger() - c2.toInteger()));
        rs.setOutlineThickness(1);
        window.draw(rs);
        draw_window();
    }

    void DesktopRenderer::drawCircle(int x, int y, int r, Color c, bool filled) {
        sf::Color c2 = c == Color::White ? sf::Color::White : sf::Color::Black;
        check_and_clear();
        sf::CircleShape cs(r, 40);
        cs.setPosition(x - r, y - r);
        if(filled)
            cs.setFillColor(c2);
        cs.setOutlineThickness(1);
        window.draw(cs);
        draw_window();
    };
    void DesktopRenderer::clearScreen(Color c) {
        sf::Color c2 = c == Color::White ? sf::Color::White : sf::Color::Black;
        check_and_clear();
        sf::RectangleShape clearRect;
        clearRect.setSize(sf::Vector2f(this->w, this->h));
        clearRect.setPosition(0, 0);
        clearRect.setFillColor(c2);
        window.draw(clearRect);
        draw_window();
    };

