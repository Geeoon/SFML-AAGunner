#include "Plane.h"

Plane::Plane(float x, float y, double velocity) : x{ x }, y{ y }, velocity{ velocity } {
	sprite.setPointCount(3);
	sprite.setRadius(5);
	sprite.setScale(sf::Vector2f{ 1.0f, 2.0f });
	sprite.rotate(90);
	sprite.setFillColor(sf::Color::Black);
	sprite.setOutlineColor(sf::Color{ 0, 255, 65 });
	sprite.setOutlineThickness(2);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	sprite.setPosition(x, y);
}

sf::CircleShape& Plane::getSprite() {
	return sprite;
}

void Plane::update(double t) {
	x += static_cast<float>(t * velocity);
	sprite.setPosition(x, y);
}

float Plane::getX() {
	return x;
}

float Plane::getY() {
	return y;
}

void Plane::reflect() {
	velocity = -velocity;
	sprite.setScale(sf::Vector2f{sprite.getScale().x, -sprite.getScale().y});
}