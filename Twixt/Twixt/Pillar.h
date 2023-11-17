#pragma once
#include<SFML/Graphics.hpp>
#define DOT_RADIUS 10
class Pillar {
private:
	sf::CircleShape shape; //forma pilonului
	sf::Color color; // culoarea
	sf::Vector2f m_position;
public:
	Pillar(float x, float y, sf::Color c);
	Pillar() = default;
	sf::Vector2f GetPosition() const;
	sf::Vector2f getCenter() const;
	void Draw(sf::RenderWindow& boardWindow);// desenare pilon intr-o fereastra
	void setPosition(const sf::Vector2f& position);
	
	

};