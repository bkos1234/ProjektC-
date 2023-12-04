#include "EnemyManager.h"
#include "ProjectileManager.h"

void EnemyManager::addEnemy(sf::Vector2f startPosition, ProjectileManager& projectileManager, int maxHealth)
{
	enemies.emplace_back(startPosition, projectileManager, maxHealth);
}

void EnemyManager::update(sf::Vector2f playerPosition)
{
	for (auto& enemy : enemies)
	{
		enemy.update(playerPosition);
	}
}

void EnemyManager::draw(sf::RenderWindow& window)
{
	for (const auto& enemy : enemies)
	{
		enemy.draw(window);
	}
}