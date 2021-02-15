#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ParticleSystem.h"

class Bullet {
public:
	Bullet(float x, float y, float heading, double velocity, sf::RenderTexture& texture, std::vector<std::shared_ptr<Bullet>>& holdingVector);
	~Bullet() = default;
	void update(double t);
	sf::RectangleShape& getSprite();
private:
	bool isInBounds();
	std::vector<std::shared_ptr<Bullet>>& holdingVector;
	sf::RenderTexture& texture;
	sf::RectangleShape sprite;
	sf::Clock timer;
	float x, y;
	const float heading;
	const double velocity;
};