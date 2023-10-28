#include "Board.h"

Board::Board()
	:m_size(24),
	m_tileSize(30)
{
	for (int i = 0; i < m_size; ++i)
	{
		for (int j = 0; j < m_size; ++j)
		{
			sf::RectangleShape tile(sf::Vector2f(m_tileSize, m_tileSize));
			tile.setPosition(i * m_tileSize, j * m_tileSize);
			tile.setOutlineColor(sf::Color::Black);
			tile.setOutlineThickness(1);
			m_tiles.push_back(tile);
		}
	}
}
void Board::Draw(sf::RenderWindow& window)
{
	// Calculate the dimensions of the array
	float totalBoardWidth = m_size * m_tileSize;
	float totalBoardHeight = m_size * m_tileSize;

	// Calculate the distance between the corner of the window and the window to be centered
	float offsetX = (window.getSize().x - totalBoardWidth) / 2;
	float offsetY = (window.getSize().y - totalBoardHeight) / 2;

	for (auto& tile : m_tiles)
	{
		sf::RectangleShape centeredTile = tile;
		centeredTile.setPosition(tile.getPosition().x + offsetX, tile.getPosition().y + offsetY); // Centering each tile of the array using the previously calculated offset
		window.draw(centeredTile);
	}
}
