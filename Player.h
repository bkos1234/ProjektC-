#pragma once
#include <SFML/Graphics.hpp>
class Environment;
class ProjectileManager;

class Player
{
public:
	Player(const std::string& filename, float x, float y);

	void move(float x, float y);
	void input(const Environment& environment, sf::RenderWindow& window, ProjectileManager& projectileManager);
	void update();
	void draw(sf::RenderWindow& window);
	bool checkCollision(const sf::FloatRect& obstacle) const;
	void revertToLastSafePosition(); // cofa do ostatniej bezpiecznej pozycji
	sf::FloatRect getBounds() const;
	void setLastSafePosition(const sf::Vector2f & newPosition);
	sf::Vector2f getPosition() const;
	sf::Vector2f getLastSafePosition() const;

	void decreaseHealth(int amount); // zmniejsza poziom zdrowia
	int getHealth() const; // zwraca poziom zdrowia
	int getMaxHealth() const; // zwraca maksymalny poziom zdrowia
	bool isDead() const; // sprawdza czy gracz jest martwy

	void setHealth(int value);

	void shoot(ProjectileManager& projectileManager, sf::Vector2f targetPosition, float speed);

	void reset();

private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::Vector2f lastSafePosition;
	float speed = 10;
	sf::Vector2f pozycja0 = { 0,0 };
	int health;
	int maxHealth;
	sf::Clock shootCooldown;
	const float minShootCooldown = 0.5f;
};