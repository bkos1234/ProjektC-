#include "Game.h"

Game::Game(sf::RenderWindow& window) : window(window), menu(window), player("player.png", 100, 100), isRunning(true), environment(128), ui(player), isPlayerDead(false), currentState(GameState::MainMenu), currentLevel(1), deadEnemiesCount(0), totalEnemiesCount(0), isLevelRandom(false)
{
	window.setFramerateLimit(60);
}

void Game::run()
{
	while (isRunning)
	{
		processEvents();
		update();
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			isRunning = false;
			window.close();
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				if (currentState == GameState::Playing) {
					currentState = GameState::Paused;
				}
				else if (currentState == GameState::Paused) {
					currentState = GameState::Playing;
				}
				else if (currentState == GameState::LevelSelection) {
					currentState = GameState::MainMenu;
				}
				else if (currentState == GameState::HowToPlay) {
					currentState = GameState::MainMenu;
				}
			}
		}
		else if (currentState == GameState::MainMenu)
		{
			menu.handleInput(event);
		}
		else if (currentState == GameState::LevelSelection)
		{
			menu.handleLevelSelectionInput(event);
			if (menu.isLevel1ButtonPressed())
			{
				loadMapFromFile("level1.txt");
			}
			else if (menu.isLevel2ButtonPressed())
			{
				loadMapFromFile("level2.txt");
			}
			else if (menu.isLevel3ButtonPressed())
			{
				loadMapFromFile("level3.txt");
			}
			else if (menu.isLevel4ButtonPressed())
			{
				loadMapFromFile("level4.txt");
			}
			else if (menu.isLevel5ButtonPressed())
			{
				loadMapFromFile("level5.txt");
			}
			else if (menu.isGenerateLevelButtonPressed())
			{
				environment.generateMapData();
			}
		}
		else if (currentState == GameState::Paused)
		{
			menu.handlePauseInput(event);
		}
		else if (currentState == GameState::Completed)
		{
			menu.handleCompletedInput(event);
		}
		else if (currentState == GameState::Death)
		{
			menu.handleDeathInput(event);
		}
		else if (currentState == GameState::HowToPlay)
		{
			menu.handleInfoInput(event);
		}
	}

	switch (currentState)
	{
	case GameState::MainMenu:
		if (menu.isStartButtonPressed()) {
			changeState(GameState::LevelSelection);
			menu.setStartButtonPressed(false);
		}
		else if (menu.isExitButtonPressed()) {
			isRunning = false;
		}
		else if (menu.isInfoButtonPressed()) {
			changeState(GameState::HowToPlay);
		}
		break;
	case GameState::LevelSelection:
		if (menu.isLevel1ButtonPressed()) {
			isLevelRandom = false;
			currentLevel = 1;
			changeState(GameState::Playing);
			menu.setLevel1ButtonPressed(false);
		}
		else if (menu.isLevel2ButtonPressed()) {
			isLevelRandom = false;
			currentLevel = 2;
			changeState(GameState::Playing);
			menu.setLevel2ButtonPressed(false);
		}
		else if (menu.isLevel3ButtonPressed()) {
			isLevelRandom = false;
			currentLevel = 3;
			changeState(GameState::Playing);
			menu.setLevel2ButtonPressed(false);
		}
		else if (menu.isLevel4ButtonPressed()) {
			isLevelRandom = false;
			currentLevel = 4;
			changeState(GameState::Playing);
			menu.setLevel2ButtonPressed(false);
		}
		else if (menu.isLevel5ButtonPressed()) {
			isLevelRandom = false;
			currentLevel = 5;
			changeState(GameState::Playing);
			menu.setLevel2ButtonPressed(false);
		}
		else if (menu.isGenerateLevelButtonPressed()) {
			isLevelRandom = true;
			changeState(GameState::Playing);
			menu.setGenerateLevelButtonPressed(false);
		}
		break;
	case GameState::Playing:
		player.input(environment, window, projectileManager);
		ui.load();
		if (projectileManager.checkPlayerCollision(player.getBounds()))
		{
			player.decreaseHealth(40);
		}
		break;
	case GameState::Paused:
		if (menu.isResumeButtonPressed()) {
			changeState(GameState::Playing);
		}
		else if (menu.isExitToMainButtonPressed()) {
			reset();
			changeState(GameState::MainMenu);
			menu.setExitToMainButtonPressed(false);
		}
	case GameState::Death:
		if (menu.isExitToMainButtonPressed()) {
			reset();
			changeState(GameState::MainMenu);
			menu.setExitToMainButtonPressed(false);
			currentLevel = 0;
		}
	case GameState::Completed:
		if (menu.isNextLevelButtonPressed()) {
			currentLevel++;
			reset();
			changeState(GameState::Playing);
			loadMapFromFile("level" + std::to_string(currentLevel) + ".txt");
			menu.setNextLevelButtonPressed(false);
		}
		else if (menu.isExitToMainButtonPressed()) {
			reset();
			changeState(GameState::LevelSelection);
			reset();
			menu.setExitToMainButtonPressed(false);
		}
	case GameState::HowToPlay:
		if (menu.isExitToMainButtonPressed()) {
			changeState(GameState::MainMenu);
		}
	}
}

void Game::update()
{
	bool allEnemiesDead = true;
	std::vector<Enemy>& enemies = enemyManager.getEnemies();
	switch (currentState)
	{
	case GameState::Playing:
		ui.updateEnemiesCount(deadEnemiesCount,totalEnemiesCount);
		for (const auto& treeBox : environment.treeCollisionBoxes) {
			if (player.checkCollision(treeBox)) {
				player.revertToLastSafePosition();
			}
		}

		for (const auto& tree2Box : environment.tree2CollisionBoxes) {
			if (player.checkCollision(tree2Box)) {
				player.revertToLastSafePosition();
			}
		}

		for (const auto& rockBox : environment.stoneCollisionBoxes) {
			if (player.checkCollision(rockBox)) {
				player.revertToLastSafePosition();
			}
		}

		for (const auto& waterBox : environment.waterCollisionBoxes) {
			if (player.checkCollision(waterBox)) {
				player.revertToLastSafePosition();
			}
		}

		for (const auto& lavaBox : environment.lavaCollisionBoxes) {
			if (player.checkCollision(lavaBox)) {
				player.decreaseHealth(1);
			}
		}
		player.update();
		enemyManager.update(player.getPosition());
		projectileManager.update();
		projectileManager.checkCollisions(environment); // sprawdza kolizje pociskow z obiektami i usuwa pociski ktore maja kolizje
		projectileManager.checkEnemyCollisions(enemies);

		deadEnemiesCount = 0; // zerujemy licznik pokonanych przeciwnik�w
		for (const auto& enemy : enemyManager.getEnemies()) {
			if (enemy.isDead()) {
				deadEnemiesCount++; // zwi�kszamy licznik pokonanych przeciwnik�w
			}
		}



		// sprawdza czy wszystkie obiekty klasy Enemy s� martwe
		for (const auto& enemy : enemyManager.getEnemies()) {
			if (!enemy.isDead()) {
				allEnemiesDead = false;
				break;
			}
		}

		if (allEnemiesDead && isLevelRandom == false) {
			changeState(GameState::Completed);
		}
		break;

	case GameState::Completed:
		if (currentLevel == 1)
		{
			menu.level1Completed = true;
		}
		else if (currentLevel == 2)
		{
			menu.level2Completed = true;
		}
		else if (currentLevel == 3)
		{
			menu.level3Completed = true;
		}
		else if (currentLevel == 4)
		{
			menu.level4Completed = true;
		}
		else if (currentLevel == 5)
		{
			menu.level5Completed = true;
		}
		break;
	}
	menu.update();
}

void Game::render()
{
	window.clear();
	switch (currentState)
	{
	case GameState::MainMenu:
		menu.draw();
		break;
	case GameState::LevelSelection:
		menu.drawLevelSelectionMenu();
		break;
	case GameState::Playing:
		environment.draw(window);
		player.draw(window);
		enemyManager.draw(window);
		projectileManager.draw(window);
		ui.draw(window);
		if (player.isDead())
		{
			handlePlayerDeath();
		}
		break;
	case GameState::Death:
		menu.drawDeathScreen(window);
		break;
	case GameState::Paused:
		environment.draw(window);
		player.draw(window);
		enemyManager.draw(window);
		projectileManager.draw(window);
		menu.drawPauseMenu();
		break;
	case GameState::Completed:
		environment.draw(window);
		player.draw(window);
		enemyManager.draw(window);
		projectileManager.draw(window);
		if (currentLevel == 5) // je�li uko�czono ostatni poziom to nie ma przycisku "nast�pny poziom"
		{
			menu.drawLastLevelCompletedScreen();
		}
		else
		{
			menu.drawCompletedScreen();
		}
		break;
	case GameState::HowToPlay:
		menu.drawInfoScreen(window);
	}
	window.display();
}

void Game::handlePlayerDeath()
{
	changeState(GameState::Death);
}

void Game::changeState(GameState newState)
{
	currentState = newState;
}

void Game::reset()
{
	environment.reset();
	enemyManager.reset();
	player.reset();
	deadEnemiesCount = 0;
	totalEnemiesCount = 0;
}

void Game::loadMapFromFile(const std::string& filename) {
	//environment.clearSprites();
	environment.loadMapFromFile(filename); // wczytaj map� z pliku
	enemyManager.loadEnemiesFromFile(filename, projectileManager); // wczytaj przeciwnik�w z tego samego pliku
	totalEnemiesCount = enemyManager.getTotalEnemiesCount();
}

int Game::getDeadEnemiesCount() const
{
	return deadEnemiesCount;
}

int Game::getTotalEnemiesCount() const
{
	return totalEnemiesCount;
}

