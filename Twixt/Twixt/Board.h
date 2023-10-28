#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Board
{
public:
	Board();
	void Draw(sf::RenderWindow& window);
private:
	std::vector<sf::RectangleShape> m_tiles;
	int m_size;
	float m_tileSize;

};

