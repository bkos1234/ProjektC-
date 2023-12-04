#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Projectile
{
public:
	Projectile(sf::Vector2f startPosition, sf::Vector2f targetPosition, float speed, const std::string& texturePath, bool isPlayerProjectile);

	void update();
	void draw(sf::RenderWindow& window);
	bool checkCollision(const sf::FloatRect& obstacle) const;
	sf::FloatRect getBounds() const;
	bool isPlayerProjectile;

private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f velocity;
};