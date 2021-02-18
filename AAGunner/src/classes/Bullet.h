#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ParticleExploder.h"

class Bullet : public sf::Drawable {
public:
	Bullet(float x, float y, float heading, float velocity, sf::RenderTexture& texture, std::vector<std::unique_ptr<Bullet>>& holdingVector);
	~Bullet() = default;
	void update(double t);
	void setAcceleration(sf::Vector2f a);
	sf::RectangleShape& getSprite();
	void explode();
	float getX();
	float getY();

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::unique_ptr<ParticleSystem> particleSystem;
	bool isInBounds() const;
	std::vector<std::unique_ptr<Bullet>>& holdingVector;
	sf::RenderTexture& texture;
	sf::RectangleShape sprite;
	sf::Vector2f acceleration;
	sf::Clock timer;
	float x, y, vx, vy;
	bool exploded;
	const float heading;
};