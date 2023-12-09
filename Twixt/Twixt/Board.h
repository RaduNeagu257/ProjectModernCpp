#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <tuple>
#include "Pillar.h"
#include "Bridge.h"
#define DOT_RADIUS 10
#define LINE_THICKNESS 3

class Board
{
	
public:
	Board();
	void Draw(sf::RenderWindow& BoardWndow);
	void SetBoardSize(U8 size);
	void SetPillarNumber(U8 pillarNumber);
	void PlaceBridge(Pillar& selectedPillar, std::vector<Pillar>& existingPillars, std::vector<Bridge>& existingBridges, sf::Color player);
	bool isMaxBridgesReached() const;

	U8 m_boardSize1;
	U8 m_boardSize2;
	U8 m_boardSize3;
	U8 m_pillarNumberDef;
	U8 m_pillarNumber1;
	U8 m_pillarNumber2;
	U8 m_pillarNumber3;
	U8 m_bridgesNumberDef;
	U8 m_bridgesNumber1;
	U8 m_bridgesNumber2;
	U8 m_bridgesNumber3;



	sf::RectangleShape button18x18;
	sf::RectangleShape button24x24;
	sf::RectangleShape button30x30;
	sf::RectangleShape button28pillars;
	sf::RectangleShape button50pillars;
	sf::RectangleShape button78pillars;
	sf::RectangleShape button25bridges;
	sf::RectangleShape button50bridges;
	sf::RectangleShape button75bridges;

	// void PlaceBridge(Pillar& selectedPillar, std::vector<Pillar>& existingPillars, std::vector<Bridge>& existingBridges, sf::Color player);
	
	std::vector<std::tuple<sf::CircleShape, U8, U8>> getTiles();
	U8 getTileSize();
	U8 GetSize();
	void DrawSettingsButtons(sf::RenderWindow& settingsWindow);
	void SwapLines();
	static bool IsPillarThere(const std::vector<Pillar>& pillars, const Pillar& tempPillar);
	static void PlacePillar(Board& board, std::vector<Pillar>& pillars, Pillar& tempPillar, sf::Color& player, U16& pillarAdded);
	static void SwapSides(std::vector<Pillar>& redPillars, std::vector<Pillar>& blackPillars);
	bool PlacePillarInBase(Pillar& pilar);
private:
	//std::vector<sf::CircleShape> m_tiles;
	std::vector<std::tuple<sf::CircleShape, U8, U8>> m_tiles;
	U8 m_size;
	int redBridgeCount = 0;
	int blackBridgeCount = 0;
	const int maxBridges = 4;
	float m_tileSize;
	sf::RectangleShape m_horizontalLine1;
	sf::RectangleShape m_horizontalLine2;
	sf::RectangleShape m_verticalLine1;
	sf::RectangleShape m_verticalLine2;
};
