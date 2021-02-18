#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include "Player.h"
#include "Plane.h"

class PlaneManager {
public:
	PlaneManager(size_t num, std::unique_ptr<Player>& player, const sf::RenderTexture& t);
	void update();
	sf::Sprite getSprite();

private:
	std::unique_ptr<Player>& player;
	sf::RenderTexture texture;
	std::vector<std::unique_ptr<Plane>> planes;
	sf::Clock clock;
	int xBound, yBound;
};