#pragma once
#include <SFML/Graphics.hpp>
#include"Pillars.h"
#include <vector>
#define DOT_RADIUS 5
#define LINE_THICKNESS 3

class Board
{
public:
	Board();
	void Draw(sf::RenderWindow& BoardWindow);
private:
	std::vector<sf::CircleShape> m_tiles;
	int m_size;
	float m_tileSize;
	sf::RectangleShape m_redHorizontalLine1;
	sf::RectangleShape m_redHorizontalLine2;
	sf::RectangleShape m_blackVerticalLine1;
	sf::RectangleShape m_blackVerticalLine2;
};

