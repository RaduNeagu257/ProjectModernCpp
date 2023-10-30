#include "Board.h"
#include "Pillars.h"
Board::Board()
	:m_size(24),
	m_tileSize(30)
{
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
	// În constructorul Board::Board()
	Pillar blackPillar(100.0f, 100.0f, sf::Color::Black);  // Exemplu de pilon negru
	Pillar redPillar(150.0f, 150.0f, sf::Color::Red);      // Exemplu de pilon roșu

	// În metoda Board::Draw(sf::RenderWindow& window)
	blackPillar.draw(BoardWindow);
	redPillar.draw(BoardWindow);

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
}
