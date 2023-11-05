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
void Pillar::Draw(sf::RenderWindow& boardWindow)
{
	boardWindow.draw(shape);
}