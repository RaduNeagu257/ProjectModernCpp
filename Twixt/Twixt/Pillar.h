#pragma once
#include<SFML/Graphics.hpp>
#include <cstdint>

#define DOT_RADIUS 10
#define U8 uint8_t
#define U16 uint16_t

class Pillar {
private:
	sf::CircleShape shape; //forma pilonului
	sf::Color color; // culoarea
	sf::Vector2f m_position;
public:
	Pillar(float x, float y, sf::Color c,U8 row,U8 col);
	Pillar() = default;
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetCenter() const;
	sf::Color GetColor() const;
	float GetRadius() const;
	void Draw(sf::RenderWindow& boardWindow);// desenare pilon U8r-o fereastra
	void SetPosition(const sf::Vector2f& position);
	void SetColor(sf::Color color);
	U8 m_row;
	U8 m_col;

	friend bool operator==(const Pillar& lhs, const Pillar& rhs);
	friend bool operator!=(const Pillar& lhs, const Pillar& rhs);
	
	

};