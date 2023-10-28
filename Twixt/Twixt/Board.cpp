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
	for (auto& tile : m_tiles)
	{
		window.draw(tile);
	}
}
