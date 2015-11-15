//
// Created by mihau on 11/10/15.
//

#include "arduinoRenderer.h"


ArduinoRenderer::ArduinoRenderer(int w, int h){
    this->w = w;
    this->h = h;
}

int ArduinoRenderer::screenWidth() {
    return this->w;
}
int ArduinoRenderer::screenHeight() {
    return this->h;
}

void ArduinoRenderer::check_and_clear() {
    using namespace sf;
    if(window.isOpen()) {

        Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {


                mockInputDevice.setAngle(angleForKey(event.key.code));

            }
            if (event.type == Event::KeyReleased) {
                if(mockInputDevice.getAngle() == angleForKey(event.key.code))
                    mockInputDevice.setAngle(0);
            }
        }
    }
}

void ArduinoRenderer::draw_window() {
    if(window.isOpen()) window.display();
}

void ArduinoRenderer::drawRect(int x0, int y0, int w1, int h1, Color c, bool filled) {
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

void ArduinoRenderer::drawCircle(int x, int y, int r, Color c, bool filled) {
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
void ArduinoRenderer::clearScreen(Color c) {
    sf::Color c2 = c == Color::White ? sf::Color::White : sf::Color::Black;
    check_and_clear();
    sf::RectangleShape clearRect;
    clearRect.setSize(sf::Vector2f(this->w, this->h));
    clearRect.setPosition(0, 0);
    clearRect.setFillColor(c2);
    window.draw(clearRect);
    draw_window();
};

