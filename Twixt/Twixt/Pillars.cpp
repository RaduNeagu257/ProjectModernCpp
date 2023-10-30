#include "Pillars.h"
#include "Board.h"
#define DOT_RADIUS 5
Pillar::Pillar(float x, float y, sf::Color c): shape(DOT_RADIUS),color(c)
{
	shape.setPosition(x, y);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(1);
	shape.setFillColor(color);
}
void Pillar::draw(sf::RenderWindow& BoardWindow)
{
	BoardWindow.draw(shape);
}
