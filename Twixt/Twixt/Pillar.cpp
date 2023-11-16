#include "Pillar.h"
#include "Board.h"

Pillar::Pillar(float x, float y, sf::Color c) 
	: shape(DOT_RADIUS), color(c) 
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
