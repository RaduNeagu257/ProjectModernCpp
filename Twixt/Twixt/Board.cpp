#include "Board.h"
#include "Pillars.h"
Board::Board()
	:m_size(24),
	m_tileSize(30),
	m_boardSize1(18),
	m_boardSize2(20),
	m_boardSize3(16)
{
	button18x18.setSize({ 100, 50 });
	button18x18.setFillColor(sf::Color::White);
	button18x18.setPosition(50, 50); // Ajustează poziția după necesitate

	button20x20.setSize({ 100, 50 });
	button20x20.setFillColor(sf::Color::White);
	button20x20.setPosition(50, 110); // Ajustează poziția după necesitate

	button16x16.setSize({ 100, 50 });
	button16x16.setFillColor(sf::Color::White);
	button16x16.setPosition(50, 170);

	for (int i = 0; i < m_size; ++i)
	{
		for (int j = 0; j < m_size; ++j)
		{
			// Create the 2D array for the board
			sf::CircleShape tile(DOT_RADIUS);
			tile.setPosition(i * m_tileSize, j * m_tileSize);
			tile.setOutlineColor(sf::Color::Black);
			tile.setOutlineThickness(1);
			m_tiles.push_back(tile);
		}
	}


	// Create the red horizontal lines
	float lineWidth = (m_tileSize + 1) * m_size;
	m_redHorizontalLine1.setSize({ lineWidth, LINE_THICKNESS });
	m_redHorizontalLine1.setFillColor(sf::Color::Red);
	m_redHorizontalLine1.setPosition(0, m_tileSize);

	m_redHorizontalLine2.setSize({ lineWidth, LINE_THICKNESS });
	m_redHorizontalLine2.setFillColor(sf::Color::Red);
	m_redHorizontalLine2.setPosition(0, (m_size - 1) * m_tileSize - 2);

	// Create the black vertical lines
	float lineHeight = (m_tileSize + 1) * m_size;
	m_blackVerticalLine1.setSize({ LINE_THICKNESS, lineHeight });
	m_blackVerticalLine1.setFillColor(sf::Color::Black);
	m_blackVerticalLine1.setPosition(m_tileSize, 0);

	m_blackVerticalLine2.setSize({ LINE_THICKNESS, lineHeight });
	m_blackVerticalLine2.setFillColor(sf::Color::Black);
	m_blackVerticalLine2.setPosition((m_size - 1) * m_tileSize - 2, 0);
}

void Board::Draw(sf::RenderWindow& BoardWindow)
{
	//Pillar blackPillar(100.0f, 100.0f, sf::Color::Black);
	//Pillar redPillar(150.0f, 150.0f, sf::Color::Red);
	// Calculate the dimensions of the array
	float totalBoardWidth = m_size * m_tileSize;
	float totalBoardHeight = m_size * m_tileSize;


	// Calculate the distance between the corner of the window and the window to be centered
	float offsetX = (BoardWindow.getSize().x - totalBoardWidth) / 2;
	float offsetY = (BoardWindow.getSize().y - totalBoardHeight) / 2;

	// Create the background rectangle
	sf::RectangleShape backgroundRectangle(sf::Vector2f(totalBoardWidth + m_size, totalBoardHeight + m_size));

	// Set its position to the top-left corner of the array
	backgroundRectangle.setPosition(offsetX - m_tileSize * 0.8, offsetY - m_tileSize * 0.8);

	// Set its color to rgb(247, 255, 208)
	backgroundRectangle.setFillColor(sf::Color(247, 255, 208));

	// Draw the background rectangle
	BoardWindow.draw(backgroundRectangle); // draw the colored rectangle

	// Centering the array using the previously calculated offsets
	for (auto& tile : m_tiles)
	{
		sf::CircleShape centeredTile = tile;
		centeredTile.setPosition(tile.getPosition().x + offsetX, tile.getPosition().y + offsetY);
		BoardWindow.draw(centeredTile);
	}
	// Declare the mousePosition and mousePostionFloat variables.
	sf::Vector2i mousePosition;
	sf::Vector2f mousePositionFloat;

	// Get the position of the mouse.
	mousePosition = sf::Mouse::getPosition(BoardWindow);

	// Convert the mousePosition to a sf::Vector2f object.
	mousePositionFloat = sf::Vector2f(mousePosition.x, mousePosition.y);

	// Check if the mouse is over a cell.
	int x = mousePositionFloat.x / m_tileSize;
	int y = mousePositionFloat.y / m_tileSize;

	// If the mouse is over a cell, create and draw a pillar.
	if (x >= 0 && x < m_size && y >= 0 && y < m_size) {
		// Create a new pillar.
		Pillar pillar(x * m_tileSize, y * m_tileSize, sf::Color::Red);

		// Set the position of the pillar.
		pillar.setPosition(mousePositionFloat);

		// Draw the pillar.
		pillar.draw(BoardWindow);
	}

	// Position of the red and black lines showing the borders of each player
	m_redHorizontalLine1.setPosition(offsetX - m_tileSize * 0.8, offsetY + DOT_RADIUS * 3.5);
	m_redHorizontalLine2.setPosition(offsetX - m_tileSize * 0.8, offsetY + (m_size - 1) * m_tileSize - DOT_RADIUS * 2);
	m_blackVerticalLine1.setPosition(offsetX + DOT_RADIUS * 3.5, offsetY - m_tileSize * 0.8);
	m_blackVerticalLine2.setPosition(offsetX + (m_size - 1) * m_tileSize - DOT_RADIUS * 2, offsetY - m_tileSize * 0.8);
	BoardWindow.draw(m_redHorizontalLine1);
	BoardWindow.draw(m_redHorizontalLine2);
	BoardWindow.draw(m_blackVerticalLine1);
	BoardWindow.draw(m_blackVerticalLine2);
	//blackPillar.draw(BoardWindow);
	//redPillar.draw(BoardWindow);
	BoardWindow.draw(button18x18);
	BoardWindow.draw(button20x20);
	BoardWindow.draw(button16x16);
}//
void Board::SetBoardSize(int size)
{
	m_size = size;
	m_tileSize = 30; // Setează dimensiunea inițială a fiecărui pătrat
	m_tiles.clear(); // Curăță vectorul de cercuri pentru a adăuga noi cercuri cu dimensiunile actualizate

	for (int i = 0; i < m_size; ++i)
	{
		for (int j = 0; j < m_size; ++j)
		{
			sf::CircleShape tile(DOT_RADIUS);
			tile.setPosition(i * m_tileSize, j * m_tileSize);
			tile.setOutlineColor(sf::Color::Black);
			tile.setOutlineThickness(1);
			m_tiles.push_back(tile);
		}
	}

	// Regenerează liniile orizontale roșii
	float lineWidth = (m_tileSize + 1) * m_size;
	m_redHorizontalLine1.setSize({ lineWidth, LINE_THICKNESS });
	m_redHorizontalLine1.setFillColor(sf::Color::Red);
	m_redHorizontalLine1.setPosition(0, m_tileSize);

	m_redHorizontalLine2.setSize({ lineWidth, LINE_THICKNESS });
	m_redHorizontalLine2.setFillColor(sf::Color::Red);
	m_redHorizontalLine2.setPosition(0, (m_size - 1) * m_tileSize - 2);

	// Regenerează liniile verticale negre
	float lineHeight = (m_tileSize + 1) * m_size;
	m_blackVerticalLine1.setSize({ LINE_THICKNESS, lineHeight });
	m_blackVerticalLine1.setFillColor(sf::Color::Black);
	m_blackVerticalLine1.setPosition(m_tileSize, 0);

	m_blackVerticalLine2.setSize({ LINE_THICKNESS, lineHeight });
	m_blackVerticalLine2.setFillColor(sf::Color::Black);
	m_blackVerticalLine2.setPosition((m_size - 1) * m_tileSize - 2, 0);
}

void Board::DrawSettingsButtons(sf::RenderWindow& settingsWindow)
{
	settingsWindow.draw(button18x18);
	settingsWindow.draw(button20x20);
	settingsWindow.draw(button16x16);
}

