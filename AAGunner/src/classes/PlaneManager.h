#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include "Plane.h"
#include "Bullet.h"

class PlaneManager {
public:
	PlaneManager(size_t num, const sf::RenderTexture& t);
	void update();
	sf::Sprite getSprite();

private:
	sf::RenderTexture texture;
	std::vector<std::unique_ptr<Plane>> planes;
	sf::Clock clock;
	int xBound, yBound;
};