#include "Board.h"
#include "Pillars.h"
Board::Board()
	:m_size(24),
	m_tileSize(30)
	// Initialize the pillars vector
{
	m_pillars.clear();
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
void Board::PlacePillar(int x, int y, sf::Color color) {
	// Create and add the pillar to the data structure of the board with the appropriate colors
	sf::CircleShape pillar(DOT_RADIUS);
	pillar.setPosition(x * m_tileSize, y * m_tileSize);
	pillar.setOutlineColor(sf::Color::Black);
	pillar.setOutlineThickness(1);
	pillar.setFillColor(color);
	m_pillars.push_back(pillar);

	// No need to call the Draw(boardWindow) method here; drawing is done in the main loop (main.cpp)

	// Additional logic for connections between pillars, if needed.
	// You can add logic to check connections here.

	// Update the board with the newly added pillars in the main loop
}

void Board::Draw(sf::RenderWindow& BoardWindow)
{
	//Pillar blackPillar(100.0f, 100.0f, sf::Color::Black);
	//Pillar redPillar(150.0f, 150.0f, sf::Color::Red);
	// Calculate the dimensions of the array
	float totalBoardWidth = m_size * m_tileSize;
	float totalBoardHeight = m_size * m_tileSize;
	int matrixWidth = m_size - 1;
	int matrixHeight = m_size - 1;

	// Check if the mouse is over a cell
	sf::Vector2i mousePosition;
	sf::Vector2f mousePositionFloat;
	mousePosition = sf::Mouse::getPosition(BoardWindow);
	mousePositionFloat = sf::Vector2f(mousePosition.x, mousePosition.y);

	
	// Calculate the distance between the corner of the window and the window to be centered
	float offsetX = (BoardWindow.getSize().x - totalBoardWidth) / 2;
	float offsetY = (BoardWindow.getSize().y - totalBoardHeight) / 2;
	if (mousePositionFloat.x >= offsetX + m_tileSize &&
		mousePositionFloat.x <= offsetX + matrixWidth * m_tileSize &&
		mousePositionFloat.y >= offsetY + m_tileSize &&
		mousePositionFloat.y <= offsetY + matrixHeight * m_tileSize && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		int x = static_cast<int>(mousePositionFloat.x / m_tileSize);
		int y = static_cast<int>(mousePositionFloat.y / m_tileSize);



		sf::Vector2f mousePositionFloat(mousePosition.x, mousePosition.y);
		//sf::Vector2f mousePosition = sf::Mouse::getPosition(BoardWindow);


		// If the mouse is over a cell, create and draw a pillar.
		if (x >= 0 && x < m_size && y >= 0 && y < m_size) {
			// Create a new pillar.
			Pillar pillar(x * m_tileSize, y * m_tileSize, sf::Color::Red);
			pillar.setPosition(mousePositionFloat);
			// Draw the pillar.
			pillar.draw(BoardWindow);
		}
	}


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

	// Position of the red and black lines showing the borders of each player
	m_redHorizontalLine1.setPosition(offsetX - m_tileSize * 0.8, offsetY + DOT_RADIUS * 3.5);
	m_redHorizontalLine2.setPosition(offsetX - m_tileSize * 0.8, offsetY + (m_size - 1) * m_tileSize - DOT_RADIUS * 2);
	m_blackVerticalLine1.setPosition(offsetX + DOT_RADIUS * 3.5, offsetY - m_tileSize * 0.8);
	m_blackVerticalLine2.setPosition(offsetX + (m_size - 1) * m_tileSize - DOT_RADIUS * 2, offsetY - m_tileSize * 0.8);

	// Draw the red and black lines
	BoardWindow.draw(m_redHorizontalLine1);
	BoardWindow.draw(m_redHorizontalLine2);
	BoardWindow.draw(m_blackVerticalLine1);
	BoardWindow.draw(m_blackVerticalLine2);
	//blackPillar.draw(BoardWindow);
	//redPillar.draw(BoardWindow);
	// În metoda Board::Draw(sf::RenderWindow& window)
	for (const auto& pillar : m_pillars) {
		BoardWindow.draw(pillar);
	}
}