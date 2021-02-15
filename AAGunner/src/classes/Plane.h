#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Plane {
public:
	Plane(float x, float y, double velocity);
	sf::CircleShape& getSprite();
	void update(double t);
	void reflect();
	float getX();
	float getY();

protected:
	sf::CircleShape sprite;
	float x, y;
	double velocity;
};