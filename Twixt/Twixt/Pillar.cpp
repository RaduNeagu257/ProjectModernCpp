#include "Pillar.h"
#include "Board.h"

Pillar::Pillar(float x, float y, sf::Color c,int row,int col) 
	: shape(DOT_RADIUS),
	color(c),
	m_row(row),
	m_col(col)
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

float Pillar::getRadius() const
{
	return shape.getRadius();
}

void Pillar::setColor(sf::Color color)
{
	shape.setFillColor(color);
}

sf::Vector2f Pillar::getCenter() const
{
	sf::Vector2f center = sf::Vector2f(GetPosition().x + shape.getRadius(), GetPosition().y + shape.getRadius());
	return center;
}
void Pillar::setPosition(const sf::Vector2f& position)
{
	m_position = position;
}
void Pillar::Draw(sf::RenderWindow& boardWindow)
{
	boardWindow.draw(shape);
}
