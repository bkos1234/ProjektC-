#include "Enemy.h"

Enemy::Enemy(sf::Vector2f startPosition, ProjectileManager& projectileManager) : projectileManager(projectileManager)
{
	if (!texture.loadFromFile("dinosaur.png")) {
		std::cout << "B��d podczas �adowania tekstury przeciwnika\n";
	}

	if (!texture2.loadFromFile("dinosaur_angry.png")) {
		std::cout << "B��d podczas �adowania tekstury przeciwnika\n";
	}
	texture.setSmooth(true);
	sprite.setTexture(texture);
	sprite.setPosition(startPosition);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);

	canShootFlag = true;
}

void Enemy::update(sf::Vector2f playerPosition)
{	
	if (std::abs(playerPosition.x - sprite.getPosition().x) < 400.0f)
	{
		facePlayer(playerPosition);
		sprite.setTexture(texture2);
	}
	else
	{
		sprite.setTexture(texture);
	}
	// strzelanie co 5 sekund
	if (canShoot() && std::abs(playerPosition.x - sprite.getPosition().x) < 400.0f) {
		facePlayer(playerPosition);
		shoot(playerPosition);
		resetShootTimer();
	}
}

void Enemy::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

bool Enemy::canShoot() const
{
	return canShootFlag && shootTimer.getElapsedTime().asSeconds() >= 5.0;
}

void Enemy::resetShootTimer()
{
	shootTimer.restart();
}

void Enemy::shoot(sf::Vector2f playerPosition)
{
	sf::Vector2f textureSize(sprite.getTexture()->getSize());
	sf::Vector2f mouthPosition = sprite.getPosition() + mouthOffset;
	projectileManager.addProjectile(sprite.getPosition() + mouthOffset, playerPosition, 2.5, "fireball.png");

	std::cout << "Przeciwnik strzela!\n";
}

void Enemy::facePlayer(sf::Vector2f playerPosition)
{
	float angle = 0.0f;
	if (playerPosition.x < sprite.getPosition().x) {
		// Patrzy w lewo
		angle = 0.0f;
		sprite.setScale(1, 1);
		mouthOffset = sf::Vector2f(-57, -33);
	}
	else {
		// Patrzy w prawo
		angle = 180.0f;
		sprite.setScale(1, -1);
		mouthOffset = sf::Vector2f(57, -33);
	}

	sprite.setRotation(angle);
}