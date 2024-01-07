#pragma once
#include <SFML/Graphics.hpp>
class EnemyManager;
class ProjectileManager;

struct Tile {
	int ground;
	int object;
	int enemy;
};

class Environment
{
public:

	Environment(int tileSize);
	void draw(sf::RenderWindow& window);
	void load(Tile mapData[15][8]);
	void addCollisionBox(int objectType, int i, int j, int tileSize, int treeWidth, int treeHeight);
	std::vector<sf::FloatRect> waterCollisionBoxes;
	std::vector<sf::FloatRect> treeCollisionBoxes;
	std::vector<sf::FloatRect> stoneCollisionBoxes;
	std::vector<sf::FloatRect> lavaCollisionBoxes;
	std::vector<sf::FloatRect> carCollisionBoxes;
	int getObjectWidth(int objectType); // funkcja zwracaj�ca szeroko�� obiektu
	int getObjectHeight(int objectType); // funkcja zwracaj�ca wysoko�� obiektu
	void loadMapFromFile(const std::string& filename);
	void generateMapData();
	void reset();
private:

	sf::Texture grassTexture;
	sf::Texture treeTexture;
	sf::Texture sandTexture;
	sf::Texture waterTexture;
	sf::Texture rockTexture;
	sf::Texture lavaTexture;
	sf::Texture flowerTexture;
	sf::Texture carTexture;
	sf::Sprite groundSprites[15][8];
	sf::Sprite objectSprites[15][8];
	Tile mapData[15][8];
};