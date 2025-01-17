﻿#include "Board.h"
#include <iostream>
Board::Board()
	:m_tileSize{ 30 },
	m_size{ 24 },
	m_boardSize1{ 18 },
	m_boardSize2{ 24 },
	m_boardSize3{ 30 },
	m_pillarNumberDef{ 50 },
	m_pillarNumber1{ 25 },
	m_pillarNumber2{ 50 },
	m_pillarNumber3{ 75 },
	m_bridgesNumberDef{ 50 },
	m_bridgesNumber1{ 25 },
	m_bridgesNumber2{ 50 },
	m_bridgesNumber3{ 75 },
	button18x18{ { 100, 50 } },
	button24x24{ { 100, 50 } },
	button30x30{ { 100, 50 } },
	button28pillars{ { 100, 50 } },
	button50pillars{ { 100, 50 } },
	button78pillars{ { 100, 50 } },
	button25bridges{ { 120,50 } },
	button50bridges{ { 120,50 } },
	button75bridges{ { 120, 50 } }


{
	button18x18.setFillColor(sf::Color::Black);
	button18x18.setPosition(50, 80);

	button24x24.setFillColor(sf::Color::Black);
	button24x24.setPosition(50, 140);

	button30x30.setFillColor(sf::Color::Black);
	button30x30.setPosition(50, 200);

	button28pillars.setFillColor(sf::Color::Black);
	button28pillars.setPosition(450, 80);

	button50pillars.setFillColor(sf::Color::Black);
	button50pillars.setPosition(450, 140);

	button78pillars.setFillColor(sf::Color::Black);
	button78pillars.setPosition(450, 200);

	button25bridges.setFillColor(sf::Color::Black);
	button25bridges.setPosition(800, 80);

	button50bridges.setFillColor(sf::Color::Black);
	button50bridges.setPosition(800, 140);

	button75bridges.setFillColor(sf::Color::Black);
	button75bridges.setPosition(800, 200);


	// Create the red horizontal lines
	float lineWidth = (m_tileSize + 1) * m_size;
	m_horizontalLine1.setSize({ lineWidth, LINE_THICKNESS });
	m_horizontalLine1.setFillColor(sf::Color::Red);

	m_horizontalLine2.setSize({ lineWidth, LINE_THICKNESS });
	m_horizontalLine2.setFillColor(sf::Color::Red);

	// Create the black vertical lines
	float lineHeight = (m_tileSize + 1) * m_size;
	m_verticalLine1.setSize({ LINE_THICKNESS, lineHeight });
	m_verticalLine1.setFillColor(sf::Color::Black);

	m_verticalLine2.setSize({ LINE_THICKNESS, lineHeight });
	m_verticalLine2.setFillColor(sf::Color::Black);
}

void Board::Draw(sf::RenderWindow& BoardWindow)
{
	float totalBoardWidth = m_size * m_tileSize;
	float totalBoardHeight = m_size * m_tileSize;


	// Calculate the distance between the corner of the window and the window to be centered
	float offsetX = (BoardWindow.getSize().x - totalBoardWidth) / 2;
	float offsetY = (BoardWindow.getSize().y - totalBoardHeight) / 2;

	// Create the background rectangle
	sf::RectangleShape backgroundRectangle(sf::Vector2f(totalBoardWidth + m_size, totalBoardHeight + m_size));

	// Set its position to the top-left corner of the array
	backgroundRectangle.setPosition(offsetX - m_tileSize * 0.8, offsetY - m_tileSize * 0.8);

	// Set its color to rgb(247, 255, 208) - pale yellow from pictures of the board game
	backgroundRectangle.setFillColor(sf::Color(247, 255, 208));

	// Draw the background rectangle
	BoardWindow.draw(backgroundRectangle); // draw the colored rectangle

	// Centering the array using the previously calculated offsets

	for (U8 i = 0; i < m_size; ++i)
	{
		for (U8 j = 0; j < m_size; ++j)
		{
			// Create the 2D array for the board
			sf::CircleShape tile(DOT_RADIUS);
			tile.setPosition(i * m_tileSize + offsetX, j * m_tileSize + offsetY);
			tile.setOutlineColor(sf::Color::Black);
			tile.setOutlineThickness(1);
			m_tiles.push_back(std::make_tuple(tile, j, i));
			BoardWindow.draw(tile);
		}
	}

	// Declare the mousePosition and mousePostionFloat variables.
	sf::Vector2i mousePosition;
	sf::Vector2f mousePositionFloat;

	// Get the position of the mouse.
	mousePosition = sf::Mouse::getPosition(BoardWindow);

	// Check if the mouse is hovering over a cell.

	for (auto& tile : m_tiles)
	{

		if (std::get<0>(tile).getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
		{
			// Temporarily change the color of the hovered pillar to a light grey
			std::get<0>(tile).setFillColor(sf::Color(200, 200, 200, 255));
			BoardWindow.draw(std::get<0>(tile));
		}
	}

	m_horizontalLine1.setPosition(offsetX - m_tileSize * 0.8, offsetY + DOT_RADIUS * 2.25);
	m_horizontalLine2.setPosition(offsetX - m_tileSize * 0.8, offsetY + (m_size - 1) * m_tileSize - DOT_RADIUS * 0.6);

	m_verticalLine1.setPosition(offsetX + DOT_RADIUS * 2.25, offsetY - m_tileSize * 0.8);
	m_verticalLine2.setPosition(offsetX + (m_size - 1) * m_tileSize - DOT_RADIUS * 0.6, offsetY - m_tileSize * 0.8);

	BoardWindow.draw(m_horizontalLine1);
	BoardWindow.draw(m_horizontalLine2);
	BoardWindow.draw(m_verticalLine1);
	BoardWindow.draw(m_verticalLine2);

}
void Board::SetBoardSize(const U8& size)
{
	m_size = size;
	m_tiles.clear(); // clean the tiles vector to add new tiles
	

	for (U8 i = 0; i < m_size; ++i)
	{
		for (U8 j = 0; j < m_size; ++j)
		{
			sf::CircleShape tile(DOT_RADIUS);
			tile.setPosition(i * m_tileSize, j * m_tileSize);
			tile.setOutlineColor(sf::Color::Black);
			tile.setOutlineThickness(1);
			m_tiles.push_back(std::make_tuple(tile, j, i));
		}
	}

	// Redraw the horizontal lines
	float lineWidth = (m_tileSize + 1) * m_size;
	m_horizontalLine1.setSize({ lineWidth, LINE_THICKNESS });
	m_horizontalLine1.setFillColor(sf::Color::Red);
	m_horizontalLine1.setPosition(0, m_tileSize);

	m_horizontalLine2.setSize({ lineWidth, LINE_THICKNESS });
	m_horizontalLine2.setFillColor(sf::Color::Red);
	m_horizontalLine2.setPosition(0, (m_size - 1) * m_tileSize - 2);

	// Redraw the vertical lines
	float lineHeight = (m_tileSize + 1) * m_size;
	m_verticalLine1.setSize({ LINE_THICKNESS, lineHeight });
	m_verticalLine1.setFillColor(sf::Color::Black);
	m_verticalLine1.setPosition(m_tileSize, 0);

	m_verticalLine2.setSize({ LINE_THICKNESS, lineHeight });
	m_verticalLine2.setFillColor(sf::Color::Black);
	m_verticalLine2.setPosition((m_size - 1) * m_tileSize - 2, 0);
}

bool Board::PlaceBridge(const Pillar& selectedPillar, const std::vector<Pillar>& existingPillars, std::vector<Bridge>& existingBridges,const sf::Color& player,const std::vector<Bridge>& otherBridges)
{
	if (MaxNumberBridgesReached(existingBridges))
	{
		return false;
	}
	bool found = false;
	
	for (auto& pillar : existingPillars) // check every pillar other than the previously selected one if a bridge can be placed
		if (selectedPillar != pillar) // avoid checking the same pillar
		{
			bool bridgeExists = false;

			U8 dx = std::abs(pillar.m_col - selectedPillar.m_col);
			U8 dy = std::abs(pillar.m_row - selectedPillar.m_row);
			std::cout << unsigned(dx) << " " << unsigned(dy) << "\n";

			if (((dx == 2 && dy == 1) || (dx == 1 && dy == 2))) // check if pillars are in an L shape
			{
				for (auto& bridge : existingBridges) // check all existing bridges in order to make sure that a bridge doesn't already exist between 2 pillars
					if((bridge.m_startPillar == selectedPillar && bridge.m_stopPillar == pillar) ||
					   (bridge.m_startPillar == pillar && bridge.m_stopPillar == selectedPillar))
					{
							bridgeExists = true;
							break;
					}
				if(bridgeExists == false)
					{
						found = true;
						std::cout << "intersection: " << checkIntersection(Bridge(selectedPillar, pillar, player), existingBridges, otherBridges) << "\n";
						if(!checkIntersection(Bridge(selectedPillar, pillar, player), existingBridges, otherBridges))
							existingBridges.emplace_back(selectedPillar, pillar, player);
						if (MaxNumberBridgesReached(existingBridges)) // check if number of maximum allowed bridges has been reached
						{
							
							return false;
						}
					}
			}
		}
	if (found)
		std::cout << "Placed bridge\n";
	else
		std::cout << "Did not find any pillar to place a bridge between\n";
	return true;
}

std::vector<std::tuple<sf::CircleShape, U8, U8>> Board::getTiles() const
{
	return m_tiles;
}

U8 Board::getTileSize() const
{
	return m_tileSize;
}

U8 Board::GetSize() const
{
	return m_size;
}

void Board::DrawSettingsButtons(sf::RenderWindow& settingsWindow)
{
	//text for board buttons
	sf::Text text18x18;
	sf::Font settingsfont;
	sf::Color textColor(255, 215, 0);

	settingsfont.loadFromFile("ARIAL.TTF");
	text18x18.setFont(settingsfont); // Set the font to our text
	text18x18.setString("18x18"); // Set the button label text
	text18x18.setCharacterSize(24); // Set the text size
	text18x18.setFillColor(textColor); // Set the text color

	sf::FloatRect textRectBoard = text18x18.getLocalBounds();

	// Position the text relative to the button
	text18x18.setOrigin(textRectBoard.left + textRectBoard.width / 2.0f, textRectBoard.top + textRectBoard.height / 2.0f);
	text18x18.setPosition(sf::Vector2f(button18x18.getPosition().x + button18x18.getSize().x / 2.0f, button18x18.getPosition().y + button18x18.getSize().y / 2.0f));

	sf::Text text24x24 = text18x18;

	text24x24.setString("24x24");
	// Position the text relative to the button
	text24x24.setPosition(sf::Vector2f(button24x24.getPosition().x + button24x24.getSize().x / 2.0f, button24x24.getPosition().y + button24x24.getSize().y / 2.0f));

	sf::Text text30x30 = text18x18;

	text30x30.setString("30x30");
	// Position the text relative to the button
	text30x30.setPosition(sf::Vector2f(button30x30.getPosition().x + button30x30.getSize().x / 2.0f, button30x30.getPosition().y + button30x30.getSize().y / 2.0f));

	//text for pillar buttons
	sf::Text text28Pillars;

	settingsfont.loadFromFile("ARIAL.TTF");
	text28Pillars.setFont(settingsfont); // Set the font to our text
	text28Pillars.setString("28 pillars"); // Set the button label text
	text28Pillars.setCharacterSize(24); // Set the text size
	text28Pillars.setFillColor(textColor); // Set the text color

	sf::FloatRect textRectPillars = text28Pillars.getLocalBounds();

	// Position the text relative to the button
	text28Pillars.setOrigin(textRectPillars.left + textRectPillars.width / 2.0f, textRectPillars.top + textRectPillars.height / 2.0f);
	text28Pillars.setPosition(sf::Vector2f(button28pillars.getPosition().x + button28pillars.getSize().x / 2.0f, button28pillars.getPosition().y + button28pillars.getSize().y / 2.0f));

	sf::Text text50Pillars = text28Pillars;

	text50Pillars.setString("50 pillars");
	// Position the text relative to the button
	text50Pillars.setPosition(sf::Vector2f(button50pillars.getPosition().x + button50pillars.getSize().x / 2.0f, button50pillars.getPosition().y + button50pillars.getSize().y / 2.0f));

	sf::Text text78Pillars = text28Pillars;

	text78Pillars.setString("78 pillars");
	// Position the text relative to the button
	text78Pillars.setPosition(sf::Vector2f(button78pillars.getPosition().x + button78pillars.getSize().x / 2.0f, button78pillars.getPosition().y + button78pillars.getSize().y / 2.0f));

	//text for bridges button
	sf::Text text25bridges;

	settingsfont.loadFromFile("ARIAL.TTF");
	text25bridges.setFont(settingsfont); // Set the font to our text
	text25bridges.setString("25 bridges"); // Set the button label text
	text25bridges.setCharacterSize(24); // Set the text size
	text25bridges.setFillColor(textColor); // Set the text color

	sf::FloatRect textRectBridges = text25bridges.getLocalBounds();

	// Position the text relative to the button
	text25bridges.setOrigin(textRectBridges.left + textRectBridges.width / 2.0f, textRectBridges.top + textRectBridges.height / 2.0f);
	text25bridges.setPosition(sf::Vector2f(button25bridges.getPosition().x + button25bridges.getSize().x / 2.0f, button25bridges.getPosition().y + button25bridges.getSize().y / 2.0f));

	sf::Text text50bridges = text25bridges;

	text50bridges.setString("50 bridges");
	// Position the text relative to the button
	text50bridges.setPosition(sf::Vector2f(button50bridges.getPosition().x + button50bridges.getSize().x / 2.0f, button50bridges.getPosition().y + button50bridges.getSize().y / 2.0f));

	sf::Text text75bridges = text25bridges;

	text75bridges.setString("75 bridges");
	// Position the text relative to the button
	text75bridges.setPosition(sf::Vector2f(button75bridges.getPosition().x + button75bridges.getSize().x / 2.0f, button75bridges.getPosition().y + button75bridges.getSize().y / 2.0f));

	settingsWindow.draw(button18x18);
	settingsWindow.draw(text18x18);

	settingsWindow.draw(button24x24);
	settingsWindow.draw(text24x24);

	settingsWindow.draw(button30x30);
	settingsWindow.draw(text30x30);

	settingsWindow.draw(button28pillars);
	settingsWindow.draw(text28Pillars);

	settingsWindow.draw(button50pillars);
	settingsWindow.draw(text50Pillars);

	settingsWindow.draw(button78pillars);
	settingsWindow.draw(text78Pillars);

	settingsWindow.draw(button25bridges);
	settingsWindow.draw(text25bridges);

	settingsWindow.draw(button50bridges);
	settingsWindow.draw(text50bridges);

	settingsWindow.draw(button75bridges);
	settingsWindow.draw(text75bridges);


}

void Board::SwapLines()
{
	m_horizontalLine1.setFillColor(sf::Color::Black);
	m_horizontalLine2.setFillColor(sf::Color::Black);
	m_verticalLine1.setFillColor(sf::Color::Red);
	m_verticalLine2.setFillColor(sf::Color::Red);
}

bool Board::IsPillarThere(const std::vector<Pillar>& pillars, const Pillar& tempPillar)
{
	//each existing pillar is checked in case the new pillar would be placed on a position which already has a pillar on it
	for (const auto& pillar : pillars) {
		if (pillar == tempPillar)
			return true;
	}
	return false;
}

void Board::PlacePillar(std::vector<Pillar>& pillars,const Pillar& tempPillar, U16& pillarAdded)
{
	if(!MaxNumberPillarsReached(pillars))
	{
		if (!IsPillarThere(pillars, tempPillar))
		{

			std::cout << "Pillar button clicked!" << std::endl; // debug message
			pillarAdded++;
			pillars.emplace_back(tempPillar); //pillar is added to the vector of existing pillars

		}
	}
	else
		std::cout << "There is already a pillar there!" << std::endl;

}
void Board::SwapSides(std::vector<Pillar>& redPillars, std::vector<Pillar>& blackPillars)
{
	// swap the pillars
	std::swap(redPillars, blackPillars);

	// swap the color of the pillars
	for (auto& pillar : redPillars)
		pillar.setColor(sf::Color::Red);
	for (auto& pillar : blackPillars)
		pillar.setColor(sf::Color::Black);
}

bool Board::PlacePillarInBase(const Pillar& tempPillar)
{
	// check if a pillar is to be placed in one of the inaccessible four corners of the board
	if (tempPillar.m_row == 0 && (tempPillar.m_col == 0 || tempPillar.m_col == m_size - 1))
	{
		return false;
	}
	if(tempPillar.m_row == m_size - 1 && (tempPillar.m_col == 0 || tempPillar.m_col == m_size - 1))
	{
		return false;
	}

	// check if pillar is to be placed in a base
	if (tempPillar.m_col == 0 || tempPillar.m_col == m_size - 1)
		return (tempPillar.GetColor() == m_verticalLine1.getFillColor() || tempPillar.GetColor() == m_verticalLine2.getFillColor());
	if (tempPillar.m_row == 0 || tempPillar.m_row == m_size - 1)
		return (tempPillar.GetColor() == m_horizontalLine1.getFillColor() || tempPillar.GetColor() == m_horizontalLine2.getFillColor());

	return true;
}

U8 Board::GetMaxPillarNumber() const 
{
	return m_pillarNumberDef;
}

U8 Board::GetMaxBridgeNumber() const
{
	return m_bridgesNumberDef;
}

void Board::SetMaxBridgeNumber(const U8& bridgeNumber) 
{
	m_bridgesNumberDef = bridgeNumber;
}

bool Board::MaxNumberPillarsReached(const std::vector<Pillar>& pillars)
{
	return pillars.size() >= m_pillarNumberDef;
}

bool Board::MaxNumberBridgesReached(const std::vector<Bridge>& bridges)
{
	return bridges.size() >= m_bridgesNumberDef;
}

bool Board::WinningChainCreated(const std::vector<Bridge>& bridges, const std::vector<Pillar> pillars, const sf::Color player)
{
	U8 minimumBridgesNumber = m_size / 2 + m_size % 2;
	if (bridges.size() < minimumBridgesNumber) // check if the number of placed bridges is lower than the minimum required to create a chain from one border to the next
		return false;
	if (!PillarOnOppositeSides(pillars, player))
		return false;

	std::queue<Pillar> queue;
	std::vector<Pillar> visited;

	// initialize the queue with the pillars placed on the first border depending on the player color
	if (player == sf::Color::Red)
	{
		for (auto& pillar : pillars)
			if (pillar.m_row == 0)
				queue.push(pillar);
	}
	else if (player == sf::Color::Black)
	{
		for (auto& pillar : pillars)
			if (pillar.m_col == 0)
				queue.push(pillar);
	}

	// BFS algorithm
	while (!queue.empty())
	{
		Pillar current = queue.front();
		queue.pop();

		// check if the opposite border was reached depending on the player color
		if((player == sf::Color::Red && current.m_row == m_size -1) || (player == sf::Color::Black && current.m_col == m_size - 1))
			return true;

		for (auto& bridge : bridges)
		{
			Pillar connectedPillar;
		
			// find the connected pillar to the currently selected one
			if(current == bridge.m_startPillar)
				connectedPillar = bridge.m_stopPillar;
			else if (current == bridge.m_stopPillar)
				connectedPillar = bridge.m_startPillar;

			// check if the found connected pillar has been previously found
			if(std::find(visited.begin(),visited.end(), connectedPillar) == visited.end())
			{
				queue.push(connectedPillar);
				visited.push_back(connectedPillar);
			}
		}
	}
	return false;

}
bool Board::PillarOnOppositeSides(const std::vector<Pillar>& pillars,const sf::Color& player)
{
	bool found1=false, found2 = false;
	if (player == sf::Color::Red)
	{
		// search for at least one pillar on the first row and one pillar on the last row
		for (auto& pillar : pillars)
		{
			if ((pillar.m_row == 0 && pillar.m_col > 0 && pillar.m_col < m_size - 1))
				found1 = true;
			if ((pillar.m_row == m_size-1 && pillar.m_col > 0 && pillar.m_col < m_size - 1))
				found2 = true;
			if (found1 && found2)
				return true;
		}
	}
	else if (player == sf::Color::Black)
	{	
		//search for at least one pillar on the first column and one pillar on the last column
		for (auto& pillar : pillars)
		{
			if ((pillar.m_col == 0 && pillar.m_row > 0 && pillar.m_row < m_size - 1))
				found1 = true;
			if ((pillar.m_col == m_size - 1 && pillar.m_row > 0 && pillar.m_row < m_size - 1))
				found2 = true;
			if (found1 && found2)
				return true;
		}
	}
	return false;
}


void Board::SetPillarNumber(const U8& pillarNumber)
{
	m_pillarNumberDef = pillarNumber;
}



enum Orientation { COLLINEAR, CLOCKWISE, COUNTERCLOCKWISE };

Orientation getOrientation(const sf::Vector2f& p, const sf::Vector2f& q, const sf::Vector2f& r) {
	float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0) return COLLINEAR;
	return (val > 0) ? CLOCKWISE : COUNTERCLOCKWISE;
}

bool onSegment(const sf::Vector2f& p, const sf::Vector2f& q, const sf::Vector2f& r) {
	return q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y);
}

bool linesIntersect(const sf::Vector2f& p1, const sf::Vector2f& q1, const sf::Vector2f& p2, const sf::Vector2f& q2) {
	Orientation o1 = getOrientation(p1, q1, p2);
	Orientation o2 = getOrientation(p1, q1, q2);
	Orientation o3 = getOrientation(p2, q2, p1);
	Orientation o4 = getOrientation(p2, q2, q1);

	if (o1 != o2 && o3 != o4) return true;

	if (o1 == COLLINEAR && onSegment(p1, p2, q1)) return true;
	if (o2 == COLLINEAR && onSegment(p1, q2, q1)) return true;
	if (o3 == COLLINEAR && onSegment(p2, p1, q2)) return true;
	if (o4 == COLLINEAR && onSegment(p2, q1, q2)) return true;

	return false;
}

bool Board::checkIntersection(const Bridge& newBridge, const std::vector<Bridge>& bridges1,const std::vector<Bridge>& bridges2)
{
	sf::Vector2f newStart = newBridge.m_startPillar.GetPosition();
	newStart.y = m_size - 1 - newBridge.m_startPillar.m_row;
	newStart.x = newBridge.m_startPillar.m_col;

	sf::Vector2f newEnd = newBridge.m_stopPillar.GetPosition();
	newEnd.y = m_size - 1 - newBridge.m_stopPillar.m_row;
	newEnd.x = newBridge.m_stopPillar.m_col;

	if(!bridges1.empty())
	for (const auto& existingBridge : bridges1) 
	{
		if (newBridge.m_startPillar != existingBridge.m_stopPillar && newBridge.m_stopPillar != existingBridge.m_startPillar &&
			newBridge.m_startPillar != existingBridge.m_startPillar && newBridge.m_stopPillar != existingBridge.m_stopPillar)
		{
			sf::Vector2f existingStart = existingBridge.m_startPillar.GetPosition();
			existingStart.y = m_size - 1 - existingBridge.m_startPillar.m_row;
			existingStart.x = existingBridge.m_startPillar.m_col;

			sf::Vector2f existingEnd = existingBridge.m_stopPillar.GetPosition();
			existingEnd.y = m_size - 1 - existingBridge.m_stopPillar.m_row;
			existingEnd.x = existingBridge.m_stopPillar.m_col;

			if (linesIntersect(newStart, newEnd, existingStart, existingEnd)) 
				return true; // Intersection found
		}
	}
	if(!bridges2.empty())
	for (const auto& existingBridge : bridges2) {
		if (newBridge.m_startPillar != existingBridge.m_stopPillar && newBridge.m_stopPillar != existingBridge.m_startPillar &&
			newBridge.m_startPillar != existingBridge.m_startPillar && newBridge.m_stopPillar != existingBridge.m_stopPillar)
		{
			sf::Vector2f existingStart = existingBridge.m_startPillar.GetPosition();
			existingStart.y = m_size - 1 - existingBridge.m_startPillar.m_row;
			existingStart.x = existingBridge.m_startPillar.m_col;

			sf::Vector2f existingEnd = existingBridge.m_stopPillar.GetPosition();
			existingEnd.y = m_size - 1 - existingBridge.m_stopPillar.m_row;
			existingEnd.x = existingBridge.m_stopPillar.m_col;

			if (linesIntersect(newStart, newEnd, existingStart, existingEnd)) 
				return true; // Intersection found
		}
	}

	return false;

}
