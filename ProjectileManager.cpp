#include "ProjectileManager.h"
#include "Projectile.h"


void ProjectileManager::addProjectile(sf::Vector2f startPosition, sf::Vector2f targetPosition, float speed, const std::string& texturePath, bool isPlayerProjectile)
{
	projectiles.emplace_back(startPosition, targetPosition, speed, texturePath, isPlayerProjectile);
}

void ProjectileManager::update()
{
	for (auto& projectile : projectiles)
	{
		projectile.update();
	}
}

void ProjectileManager::draw(sf::RenderWindow& window)
{
	for (auto& projectile : projectiles)
	{
		projectile.draw(window);
	}
}

bool ProjectileManager::checkPlayerCollision(sf::FloatRect playerBounds)
{
    // sprawdzanie kolizji z graczem dla ka�dego pocisku
    for (auto it = projectiles.begin(); it != projectiles.end();)
    {
        if (!it->isPlayerProjectile && it->checkCollision(playerBounds))
        {
            // pocisk trafi� gracza
            it = projectiles.erase(it);
            return true;
        }
        else
        {
            // pocisk nie trafi� gracza
            ++it;
        }
    }

    // brak trafienia dla �adnego z pocisk�w
    return false;
}

bool ProjectileManager::checkEnvironmentCollision(sf::FloatRect environmentBounds)
{
    // sprawdzanie kolizji z obiektem dla ka�dego pocisku
    for (auto it = projectiles.begin(); it != projectiles.end();)
    {
        if (it->checkCollision(environmentBounds))
        {
            // pocisk trafi� obiekt
            it = projectiles.erase(it);
            std::cout << "Pocisk trafi� obiekt";
            return true;
        }
        else
        {
            // pocisk nie trafi� obiektu
            ++it;
        }
    }

    // brak trafienia dla �adnego z pocisk�w
    return false;
}

bool ProjectileManager::checkEnemyCollision(sf::FloatRect enemyBounds)
{
    // sprawdzanie kolizji z obiektem dla ka�dego pocisku
    for (auto it = projectiles.begin(); it != projectiles.end();)
    {
        if (it->checkCollision(enemyBounds))
        {
            // pocisk trafi� obiekt
            it = projectiles.erase(it);
            std::cout << "Pocisk trafi� obiekt";
            return true;
        }
        else
        {
            // pocisk nie trafi� obiektu
            ++it;
        }
    }

    // brak trafienia dla �adnego z pocisk�w
    return false;
}