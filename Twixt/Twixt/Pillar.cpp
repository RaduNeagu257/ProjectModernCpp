#include "Pillar.h"
#include "Board.h"

Pillar::Pillar(float x, float y, sf::Color c,U8 row,U8 col) 
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

sf::Color Pillar::GetColor() const {
	return color;
}

float Pillar::GetRadius() const
{
	return shape.getRadius();
}

void Pillar::SetColor(sf::Color color)
{
	shape.setFillColor(color);
}

sf::Vector2f Pillar::GetCenter() const
{
	sf::Vector2f center = sf::Vector2f(GetPosition().x + shape.getRadius(), GetPosition().y + shape.getRadius());
	return center;
}
void Pillar::SetPosition(const sf::Vector2f & position)
{
	m_position = position;
}
void Pillar::Draw(sf::RenderWindow& boardWindow)
{
	boardWindow.draw(shape);
}
