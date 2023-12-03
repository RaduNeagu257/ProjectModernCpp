#pragma once
#include<SFML/Graphics.hpp>
#define DOT_RADIUS 10
class Pillar {
private:
	sf::CircleShape shape; //forma pilonului
	sf::Color color; // culoarea
	sf::Vector2f m_position;
public:
	Pillar(float x, float y, sf::Color c,int row,int col);
	Pillar() = default;
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetCenter() const;
	sf::Color GetColor() const;
	float GetRadius() const;
	void Draw(sf::RenderWindow& boardWindow);// desenare pilon intr-o fereastra
	void SetPosition(const sf::Vector2f& position);
	void SetColor(sf::Color color);
	int m_row;
	int m_col;
	
	

};