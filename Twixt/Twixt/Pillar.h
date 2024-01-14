#pragma once
#include<SFML/Graphics.hpp>
#include <cstdint>

#define DOT_RADIUS 10
#define U8 uint8_t
#define U16 uint16_t

class Pillar {
public:
	Pillar(const float& x,const float& y, const sf::Color& c,const U8& row,const U8& col);
	Pillar() = default;
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetCenter() const;
	sf::Color GetColor() const;
	float GetRadius() const;
	void Draw(sf::RenderWindow& boardWindow);
	void setPosition(const sf::Vector2f& position);
	void setColor(const sf::Color& color);

	U8 m_row;
	U8 m_col;
	
	friend bool operator==(const Pillar& lhs, const Pillar& rhs);
	friend bool operator!=(const Pillar& lhs, const Pillar& rhs);
private:
	sf::CircleShape shape;
	sf::Color color;
	sf::Vector2f m_position;
};