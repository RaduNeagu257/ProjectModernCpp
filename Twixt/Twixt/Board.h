#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include"Pillars.h"
#define DOT_RADIUS 5
#define LINE_THICKNESS 3

class Board
{
public:
	Board();
	void Draw(sf::RenderWindow& BoardWndow);
	void PlacePillar(int x, int y, sf::Color color);
	int m_size;
	float m_tileSize;
private:
	std::vector<sf::CircleShape> m_tiles;
	std::vector<sf::CircleShape> m_pillars;
	//int m_size;
	//float m_tileSize;
	sf::RectangleShape m_redHorizontalLine1;
	sf::RectangleShape m_redHorizontalLine2;
	sf::RectangleShape m_blackVerticalLine1;
	sf::RectangleShape m_blackVerticalLine2;
}; 