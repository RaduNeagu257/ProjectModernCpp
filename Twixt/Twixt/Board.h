#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#define DOT_RADIUS 10
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
	sf::RectangleShape button24x24;
	sf::RectangleShape button30x30;
	std::vector<sf::CircleShape> getTiles();
	int getTileSize();
	void DrawSettingsButtons(sf::RenderWindow& settingsWindow);
private:
	std::vector<sf::CircleShape> m_tiles;
	int m_size;
	float m_tileSize;
	sf::RectangleShape m_redHorizontalLine1;
	sf::RectangleShape m_redHorizontalLine2;
	sf::RectangleShape m_blackVerticalLine1;
	sf::RectangleShape m_blackVerticalLine2;
};

