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
	void SetBoardSize(int size);
	int m_boardSize1;
	int m_boardSize2;
	int m_boardSize3;
	sf::RectangleShape button18x18;
	sf::RectangleShape button20x20;
	sf::RectangleShape button16x16;
	void DrawSettingsButtons(sf::RenderWindow& settingsWindow);
private:
	std::vector<sf::CircleShape> m_tiles;
	int m_size;
	float m_tileSize;
	sf::RectangleShape m_redHorizontalLine1;
	sf::RectangleShape m_redHorizontalLine2;
	sf::RectangleShape m_blackVerticalLine1;
	sf::RectangleShape m_blackVerticalLine2;
	/*int m_boardSize1;
	int m_boardSize2;
	int m_boardSize3;*/
};

