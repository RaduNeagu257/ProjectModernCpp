#pragma once
#include<SFML/Graphics.hpp>
#include "Pillar.h"
class Bridge {
public:
	Bridge(const Pillar& startPillar, const Pillar& stopPillar, sf::Color color);
	void draw(sf::RenderWindow& Boardwindow) const;
	sf::Vector2f getStartPosition() const;
	sf::Vector2f getEndPosition() const;
	Pillar m_startPillar;
	Pillar m_stopPillar;

private:
	sf::RectangleShape shape;
	sf::Color color;
};