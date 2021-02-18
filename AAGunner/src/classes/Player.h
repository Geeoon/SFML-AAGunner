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
	int getScore();
	void giveScore(int s);
	std::vector<std::unique_ptr<Bullet>>& getBullets();

private:
	std::vector<std::unique_ptr<ParticleSystem>> particleSystems;
	std::vector<std::unique_ptr<Bullet>> bullets;
	sf::Clock clock;
	sf::RenderTexture& texture;
	sf::RectangleShape base, cannon;
	int x, y, score;
	float firingTime;
	double angle;
	const float fireRate;
};