#pragma once
#include<SFML/Graphics.hpp>
class Bridge {
private:
	sf::RectangleShape shape;
	//sf::Vector2F startPosition;
	//sf::Vector2f endPosition;
	sf::Color color;
public:
	Bridge(const sf::Vector2f& start, const sf::Vector2f& end, sf::Color color);
	void draw(sf::RenderWindow& Boardwindow);
	bool canPlaceBridge(const sf::Vector2f& potentialStart, const sf::Vector2f& potentialEnd, const std::vector<Bridge>& existingBridges);
	sf::Vector2f getStartPosition() const;
	sf::Vector2f getEndPosition() const;
};