#include "Pillar.h"
#include "Board.h"

Pillar::Pillar(const float& x,const float& y, const sf::Color& c,const U8& row,const U8& col) 
	: shape{ DOT_RADIUS },
	color{ c },
	m_row{ row },
	m_col{ col }
{
	shape.setPosition(x, y);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(1);
	shape.setFillColor(color);
}
sf::Vector2f Pillar::GetPosition() const
{
	return m_position;
}

sf::Color Pillar::GetColor() const {
	return color;
}

float Pillar::GetRadius() const
{
	return shape.getRadius();
}

void Pillar::setColor(const sf::Color& color)
{
	shape.setFillColor(color);
}

sf::Vector2f Pillar::GetCenter() const
{
	sf::Vector2f center = sf::Vector2f(GetPosition().x + shape.getRadius(), GetPosition().y + shape.getRadius());
	return center;
}
void Pillar::setPosition(const sf::Vector2f & position)
{
	m_position = position;
}
void Pillar::Draw(sf::RenderWindow& boardWindow)
{
	boardWindow.draw(shape);
}

bool operator==(const Pillar& lhs, const Pillar& rhs)
{
	// 2 pillars are "equal" when they have the same position on the board, i.e. same row and column index
	return lhs.m_row == rhs.m_row && lhs.m_col == rhs.m_col;
}

bool operator!=(const Pillar& lhs, const Pillar& rhs)
{
	// 2 pillars are "equal" when they have the same position on the board, i.e. same row and column index
	return lhs.m_row != rhs.m_row || lhs.m_col != rhs.m_col;
}