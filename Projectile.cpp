#include "Projectile.h"
#pragma once

// obiekt sie tworzy w klasie game
Projectile::Projectile(sf::Vector2f startPosition, sf::Vector2f targetPosition, float speed, const std::string& texturePath, bool isPlayerProjectile)
    : isPlayerProjectile(isPlayerProjectile)
{
    if (!texture.loadFromFile(texturePath)) {
        std::cout << "B��d podczas �adowania tekstury pocisku\n";
    }
    else {
        std::cout << "Tekstura pocisku za�adowana poprawnie\n";
    }
    sprite.setScale(0.25, 0.25);
    sf::Vector2f halfSize(sprite.getLocalBounds().width / 2.0 + 36*0.25, sprite.getLocalBounds().height / 2.0 + 86*0.25);

    // ustawienie pozycji na �rodek pocisku
    sprite.setPosition(startPosition - halfSize);
    sprite.setTexture(texture);

    sf::Vector2f direction = targetPosition - startPosition;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0.0f) {
        direction /= length;
    }

    velocity = direction * speed;
}

void Projectile::update()
{
    sprite.move(velocity);
}

void Projectile::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

bool Projectile::checkCollision(const sf::FloatRect& obstacle) const
{
    return getBounds().intersects(obstacle);
}

sf::FloatRect Projectile::getBounds() const
{
    return sprite.getGlobalBounds();
}