#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <tuple>
#define DOT_RADIUS 10
#define LINE_THICKNESS 3

class Board
{
public:
	Board();
	void Draw(sf::RenderWindow& BoardWndow);
	void SetBoardSize(int size);
	void SetPillarNumber(int pillarNumber);
	int m_boardSize1;
	int m_boardSize2;
	int m_boardSize3;
	int m_pillarNumberDef;
	int m_pillarNumber1;
	int m_pillarNumber2;
	int m_pillarNumber3;
	int m_bridgesNumberDef;
	int m_bridgesNumber1;
	int m_bridgesNumber2;
	int m_bridgesNumber3;

	sf::RectangleShape button18x18;
	sf::RectangleShape button24x24;
	sf::RectangleShape button30x30;
	sf::RectangleShape button28pillars;
	sf::RectangleShape button50pillars;
	sf::RectangleShape button78pillars;
	sf::RectangleShape button25bridges;
	sf::RectangleShape button50bridges;
	sf::RectangleShape button75bridges;

	std::vector<std::tuple<sf::CircleShape, int, int>> getTiles();
	int getTileSize();
	void DrawSettingsButtons(sf::RenderWindow& settingsWindow);
private:
	//std::vector<sf::CircleShape> m_tiles;
	std::vector<std::tuple<sf::CircleShape, int, int>> m_tiles;
	int m_size;
	float m_tileSize;
	sf::RectangleShape m_redHorizontalLine1;
	sf::RectangleShape m_redHorizontalLine2;
	sf::RectangleShape m_blackVerticalLine1;
	sf::RectangleShape m_blackVerticalLine2;
};
