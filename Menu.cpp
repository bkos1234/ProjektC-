#include "Menu.h"
#include <iostream>

Menu::Menu(sf::RenderWindow& window) : window(window), startButtonPressed(false), exitButtonPressed(false)
{
	load();
}

void Menu::load()
{
	// odst�p mi�dzy przyciskami
	const float buttonSpacing = 50.0;

	// przycisk start
	if (!startButtonTexture.loadFromFile("startButton.png")) {
		std::cout << "B��d podczas �adowania przycisku startu";
	}

	startButton.setTexture(startButtonTexture);
	startButton.setPosition(window.getSize().x / 2 - startButton.getGlobalBounds().width / 2, window.getSize().y / 2 - startButton.getGlobalBounds().height / 2 - 100);

	// przycisk ustawienia
	if (!settingsButtonTexture.loadFromFile("settingsButton.png")) {
		std::cout << "B��d podczas �adowania przycisku ustawie�";
	}

	settingsButton.setTexture(settingsButtonTexture);
	settingsButton.setPosition(window.getSize().x / 2 - settingsButton.getGlobalBounds().width / 2, startButton.getPosition().y + startButton.getGlobalBounds().height + buttonSpacing);

	// przycisk zako�cz
	if (!exitButtonTexture.loadFromFile("exitButton.png")) {
		std::cout << "B��d podczas �adowania przycisku zamykania gry";
	}

	exitButton.setTexture(exitButtonTexture);
	exitButton.setPosition(window.getSize().x / 2 - exitButton.getGlobalBounds().width / 2, settingsButton.getPosition().y + settingsButton.getGlobalBounds().height + buttonSpacing);

	// t�o
	if (!backgroundTexture.loadFromFile("background.png")) {
		std::cout << "B��d podczas �adowania t�a";
	}

	background.setTexture(backgroundTexture);
	background.setPosition(0, 0);
}

void Menu::draw() {
	window.clear();
	window.draw(background);
	window.draw(startButton);
	window.draw(settingsButton);
	window.draw(exitButton);
	window.display();
	handleInput();
}

bool Menu::isStartButtonPressed() {
	return startButtonPressed;
}

void Menu::handleInput() {
	exitButtonPressed = false;
    sf::Event event;
    while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
		{
			window.close();
			break;
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
					startButtonPressed = true;
				else if (exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) // Sprawd�, czy naci�ni�to przycisk "Zamknij Gr�"
					exitButtonPressed = true;
			}
		}
    }
}

bool Menu::isExitButtonPressed() {
	return exitButtonPressed;
}

void Menu::setStartButtonPressed(bool value)
{
	startButtonPressed = value;
}