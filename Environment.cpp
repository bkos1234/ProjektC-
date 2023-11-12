#include "Environment.h"
#include <ctime>

Environment::Environment(int tileSize)
{
	grassTexture.loadFromFile("grass.png");
	treeTexture.loadFromFile("tree.png");
	sandTexture.loadFromFile("sand.png");
	waterTexture.loadFromFile("water.png");
	rockTexture.loadFromFile("rock.png");
	flowerTexture.loadFromFile("flower.png");
	lavaTexture.loadFromFile("lava.png");

	generateMapData();
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			groundSprites[i][j].setPosition(i * tileSize, j * tileSize);
			objectSprites[i][j].setPosition(i * tileSize, j * tileSize);
		}
	}
}

void Environment::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			window.draw(groundSprites[i][j]);
			window.draw(objectSprites[i][j]);
		}
	}
}

void Environment::load(Tile mapData[15][8])
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			addCollisionBox(mapData[i][j].object, i, j, 128, getObjectWidth(mapData[i][j].object), getObjectHeight(mapData[i][j].object));
			groundSprites[i][j].setTexture(grassTexture); // ustawia wsz�dzie traw�, jako pod�og�


			if (mapData[i][j].object == 1)
			{
				objectSprites[i][j].setTexture(treeTexture);
			}
			else if (mapData[i][j].object == 2)
			{
				objectSprites[i][j].setTexture(rockTexture);
			}
			else if (mapData[i][j].object == 3)
			{
				objectSprites[i][j].setTexture(flowerTexture);
			}
			else if (mapData[i][j].object == 4)
			{
				objectSprites[i][j].setTexture(waterTexture);
			}
			else if (mapData[i][j].object == 5)
			{
				objectSprites[i][j].setTexture(lavaTexture);
			}
		}
	}
}

void Environment::addCollisionBox(int objectType, int i, int j, int tileSize, int objectWidth, int objectHeight) {
	// pocz�tkowe pozycje prostok�ta kolizji
	float x = i * tileSize + (tileSize - objectWidth) / 2.0f;
	float y = j * tileSize + (tileSize - objectHeight) / 2.0f;

	// tworzenie prostok�ta kolizji o dostosowanych wymiarach
	sf::FloatRect collisionBox(x, y, objectWidth, objectHeight);

	switch (objectType) {
	case 1: // drzewo
		treeCollisionBoxes.push_back(collisionBox);
		break;
	case 2: // kamie�
		stoneCollisionBoxes.push_back(collisionBox);
		break;
	case 4: // woda
		waterCollisionBoxes.push_back(collisionBox);
		break;
	case 5: // lawa
		lavaCollisionBoxes.push_back(collisionBox);
		break;
	}
}

void Environment::generateMapData()
{
	std::srand(std::time(0));

	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 8; ++j) {
			int groundType;
			groundType = 0;
			mapData[i][j].ground = groundType;
		}
	}

	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (mapData[i][j].ground != 2) {
				int randomValue = rand() % 100;
				int objectType;

				if (randomValue < 50) {
					objectType = 0; // nic
				}
				else if (randomValue < 65) {
					objectType = 1; // drzewo
				}
				else if (randomValue < 75) {  
					objectType = 2; // kamie�
				}
				else if (randomValue < 90) {
					objectType = 3; // kwiat
				}
				else if (randomValue < 95) {
					objectType = 4; // woda
				}
				else {
					objectType = 5; // lawa
				}
				mapData[i][j].object = objectType;
			}
		}
	}

	load(mapData);
}

int Environment::getObjectWidth(int objectType)
{
	switch (objectType)
	{
	case 1: // drzewo
		return 55;
	case 2: // kamie�
		return 80;
	case 3: // kwiat
		return 30;
	case 4: // woda
		return 100;
	case 5: // lawa
		return 80;
	default:
		return 0;
	}
}

int Environment::getObjectHeight(int objectType)
{
	switch (objectType)
	{
	case 1: // drzewo
		return 85;
	case 2: // kamie�
		return 90;
	case 3: // kwiat
		return 20;
	case 4: // woda
		return 100;
	case 5: // lawa
		return 80;
	default:
		return 0;
	}
}