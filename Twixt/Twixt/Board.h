#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <tuple>
#include <queue>
//#include <unordered_set>
#include "Pillar.h"
#include "Bridge.h"
#define DOT_RADIUS 10
#define LINE_THICKNESS 3

class Board
{
public:
	Board();
	void Draw(sf::RenderWindow& BoardWndow);
	void SetBoardSize(const U8& size);
	void SetPillarNumber(const U8& pillarNumber);
	bool PlaceBridge(const Pillar& selectedPillar, const std::vector<Pillar>& existingPillars, std::vector<Bridge>& existingBridges,const sf::Color& player,const std::vector<Bridge>& otherBridges);

	// settings for board size, maximum pillar limit and maximum bridge limit
	U8 m_boardSize1;
	U8 m_boardSize2;
	U8 m_boardSize3;
	U8 m_pillarNumberDef;
	U8 m_pillarNumber1;
	U8 m_pillarNumber2;
	U8 m_pillarNumber3;

	U8 m_bridgesNumberDef=50;
	U8 m_bridgesNumber1;
	U8 m_bridgesNumber2;
	U8 m_bridgesNumber3;


	// buttons for changing board size, maximum pillar limit and maximum bridge limit
	sf::RectangleShape button18x18;
	sf::RectangleShape button24x24;
	sf::RectangleShape button30x30;
	sf::RectangleShape button28pillars;
	sf::RectangleShape button50pillars;
	sf::RectangleShape button78pillars;
	sf::RectangleShape button25bridges;
	sf::RectangleShape button50bridges;
	sf::RectangleShape button75bridges;
	
	std::vector<std::tuple<sf::CircleShape, U8, U8>> getTiles() const;
	U8 getTileSize() const;
	U8 GetSize() const;
	U8 GetMaxPillarNumber() const;
	U8 GetMaxBridgeNumber() const;

	void DrawSettingsButtons(sf::RenderWindow& settingsWindow);
	void SwapLines();
	static bool IsPillarThere(const std::vector<Pillar>& pillars, const Pillar& tempPillar);
	void PlacePillar(std::vector<Pillar>& pillars,const Pillar& tempPillar, U16& pillarAdded);
	static void SwapSides(std::vector<Pillar>& redPillars, std::vector<Pillar>& blackPillars);
	bool PlacePillarInBase(const Pillar& tempPillar);
    void SetMaxBridgeNumber(const U8& bridgeNumber);
    bool MaxNumberPillarsReached(const std::vector<Pillar>& pillars);
	bool MaxNumberBridgesReached(const std::vector<Bridge>& bridges);
	bool WinningChainCreated(const std::vector<Bridge>& bridges, const std::vector<Pillar> pillars,const sf::Color player);
	bool PillarOnOppositeSides(const std::vector<Pillar>& pillars,const sf::Color& player);
	bool checkIntersection(const Bridge& newBridge,const std::vector<Bridge>& bridges1,const std::vector<Bridge>& bridges2);
private:
	std::vector<std::tuple<sf::CircleShape, U8, U8>> m_tiles;
	U8 m_size;
	
	float m_tileSize;
	sf::RectangleShape m_horizontalLine1;
	sf::RectangleShape m_horizontalLine2;
	sf::RectangleShape m_verticalLine1;
	sf::RectangleShape m_verticalLine2;
};
