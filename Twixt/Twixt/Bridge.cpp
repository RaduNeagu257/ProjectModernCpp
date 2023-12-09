// Bridge.cpp
#include "Bridge.h"
#include<cmath>
const float PI = 3.14159265358979323846f;
const float BRIDGE_LINE_THICKNESS = 5.0f;

Bridge::Bridge(const Pillar& startPillar, const Pillar& stopPillar, sf::Color color)
    :m_startPillar(startPillar),
    m_stopPillar(stopPillar)
{
    sf::Vector2f direction = stopPillar.GetCenter() - startPillar.GetCenter();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    // Normalize the direction vector
    sf::Vector2f normalizedDirection = direction / length;

    // Calculate perpendicular offset to center the bridge vertically
    sf::Vector2f perpendicularOffset(-normalizedDirection.y, normalizedDirection.x);
    perpendicularOffset *= BRIDGE_LINE_THICKNESS / 2.0f;

    // Set the size, rotation, and position
    shape.setSize({ length, BRIDGE_LINE_THICKNESS });
    shape.setRotation(atan2(direction.y, direction.x) * 180 / PI);
    shape.setPosition(startPillar.GetCenter() - perpendicularOffset);
    shape.setFillColor(color);
}

void Bridge::draw(sf::RenderWindow& Boardwindow) const{
    Boardwindow.draw(shape);
}
bool linesU8ersect(const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3) {
    auto s1 = p1 - p0;
    auto s2 = p3 - p2;

    float s, t;
    s = (-s1.y * (p0.x - p2.x) + s1.x * (p0.y - p2.y)) / (-s2.x * s1.y + s1.x * s2.y);
    t = (s2.x * (p0.y - p2.y) - s2.y * (p0.x - p2.x)) / (-s2.x * s1.y + s1.x * s2.y);

    return s >= 0 && s <= 1 && t >= 0 && t <= 1;
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
