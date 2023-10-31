#pragma once
#include<SFML/Graphics.hpp>

class Pillar {
private:
	sf::CircleShape shape; //forma pilonului
	sf::Color color; // culoarea
	
public:
	Pillar(float x, float y, sf::Color c);
	void draw(sf::RenderWindow& BoardWindow);// desenare pilon intr-o fereastra
	void setPosition(const sf::Vector2f& position);

};