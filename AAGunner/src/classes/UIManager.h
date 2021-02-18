#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

class UIManager {
public:
	UIManager(std::unique_ptr<Player>& player);
	UIManager(unsigned int x, unsigned int y, std::unique_ptr<Player>& player);
	bool isOpen();
	void update();
	void draw(const sf::Drawable& d);
	void display();
	sf::RenderTexture& getTexture();
	sf::RenderWindow& getWindow();
private:
	sf::RenderWindow window;
	sf::RenderTexture texture;
	std::unique_ptr<Player>& player;
};