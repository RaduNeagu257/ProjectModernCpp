// Bridge.cpp
#include "Bridge.h"
#include<cmath>
const float PI = 3.14159265358979323846f;
const float LINE_THICKNESS = 5.0f;

Bridge::Bridge(const sf::Vector2f& start, const sf::Vector2f& end, sf::Color c) {
    // Calculează direcția și lungimea podului
    sf::Vector2f direction = end - start;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    // Setează proprietățile podului
    shape.setSize({ length, LINE_THICKNESS }); // LINE_THICKNESS ar fi o constantă definită în altă parte
    shape.setRotation(atan2(direction.y, direction.x) * 180 / PI); // PI ar fi definit ca constantele matematice
    shape.setPosition(start);
    shape.setFillColor(c);
}

void Bridge::draw(sf::RenderWindow& Boardwindow) {
    Boardwindow.draw(shape);
}

bool Bridge::canPlaceBridge(const sf::Vector2f& potentialStart, const sf::Vector2f& potentialEnd, const std::vector<Bridge>& existingBridges) {
    // Aici va fi implementată logica pentru verificarea plasării podului
    // ...
    return true; // sau false dacă podul nu poate fi plasat
}

sf::Vector2f Bridge::getStartPosition() const {
    return shape.getPosition();
}

sf::Vector2f Bridge::getEndPosition() const {
    // Calculează poziția de sfârșit bazată pe poziția de început și dimensiunea formei
    sf::Vector2f size = shape.getSize();
    float rotation = shape.getRotation() / 180 * PI; // Convertește înapoi în radiani
    return sf::Vector2f(
        shape.getPosition().x + cos(rotation) * size.x,
        shape.getPosition().y + sin(rotation) * size.y
    );
}
