// Bridge.cpp
#include "Bridge.h"
#include<cmath>
const float PI = 3.14159265358979323846f;
const float BRIDGE_LINE_THICKNESS = 5.0f;

Bridge::Bridge(const sf::Vector2f& start, const sf::Vector2f& end, sf::Color c) {
    // Calculează direcția și lungimea podului
    sf::Vector2f direction = end - start;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    // Setează proprietățile podului
    shape.setSize({ length, BRIDGE_LINE_THICKNESS }); // LINE_THICKNESS ar fi o constantă definită în altă parte
    shape.setRotation(atan2(direction.y, direction.x) * 180 / PI); // PI ar fi definit ca constantele matematice
    shape.setPosition(start);
    shape.setFillColor(c);
}

void Bridge::draw(sf::RenderWindow& Boardwindow) const{
    Boardwindow.draw(shape);
}// Va trebui să implementezi această funcție pentru a verifica intersecția dintre două linii
bool linesIntersect(const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3) {
    auto s1 = p1 - p0;
    auto s2 = p3 - p2;

    float s, t;
    s = (-s1.y * (p0.x - p2.x) + s1.x * (p0.y - p2.y)) / (-s2.x * s1.y + s1.x * s2.y);
    t = (s2.x * (p0.y - p2.y) - s2.y * (p0.x - p2.x)) / (-s2.x * s1.y + s1.x * s2.y);

    return s >= 0 && s <= 1 && t >= 0 && t <= 1;
}


bool Bridge::canPlaceBridge(const sf::Vector2f& potentialStart, const sf::Vector2f& potentialEnd, const std::vector<Bridge>& existingBridges) {
    // Calculează diferențele pe axele x și y
    int dx = std::abs(potentialEnd.x - potentialStart.x);
    int dy = std::abs(potentialEnd.y - potentialStart.y);

    // Verifică dacă pozițiile corespund mișcării unui cal în șah (L shape)
    if (!((dx == 2 && dy == 1) || (dx == 1 && dy == 2))) {
        return false; // Nu este o mișcare legală de cal
    }

    // Verifică intersecțiile cu podurile existente
    for (const auto& bridge : existingBridges) {
        // Aici va trebui să implementezi o funcție care să determine dacă liniile se intersectează
        if (linesIntersect(potentialStart, potentialEnd, bridge.getStartPosition(), bridge.getEndPosition())) {
            return false; // Există o intersecție, deci nu poți plasa podul
        }
    }

    // Dacă nicio regulă nu a fost încălcată, poziția este legală pentru un pod nou
    return true;
}

// Va trebui să implementezi această funcție pentru a verifica intersecția dintre două linii



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
