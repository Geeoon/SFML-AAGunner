#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ParticleExploder.h"
#include "Bullet.h"

class Player {
public:
	Player(int x, int y, sf::RenderTexture& rt);
	void draw();
	void update(const sf::RenderWindow& w);
	void fire();
private:
	std::vector<ParticleExploder> particleSystems;
	std::vector<std::shared_ptr<Bullet>> bullets;
	sf::Clock clock;
	sf::RenderTexture& texture;
	sf::RectangleShape base, cannon;
	int x, y;
	double angle;
};