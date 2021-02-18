#include "Bullet.h"

Bullet::Bullet(float x, float y, float heading, float velocity, sf::RenderTexture& texture, std::vector<std::unique_ptr<Bullet>>& holdingVector) : 
	x{ x }, 
	y{ y }, 
	heading{ heading }, 
	texture{ texture }, 
	holdingVector{ holdingVector }, 
	exploded{ false }, 
	vx{ sinf(heading * 3.1415f / 180.0f) * static_cast<float>(velocity) },
	vy{ cosf(heading * 3.1415f / 180.0f) * static_cast<float>(velocity) }
{
	sprite.setFillColor(sf::Color::Black);
	sprite.setSize(sf::Vector2f{ 3, 5 });
	sprite.setOutlineColor(sf::Color{ 255, 65, 65 });
	sprite.setOutlineThickness(2);
	sprite.setPosition(x, y);
	sprite.setOrigin(sprite.getSize().x / 2.0f, sprite.getSize().y / 2.0f);
	sprite.setRotation(heading);
	timer.restart();
}

void Bullet::update(double t) {
	if (!exploded) {
		vy += acceleration.y * static_cast<float>(t);
		vx += acceleration.x * static_cast<float>(t);
		x += vx * static_cast<float>(t);
		y -= vy * static_cast<float>(t);
		sprite.setPosition(x, y);
	}

	if (particleSystem) {
		particleSystem->update(sf::seconds(static_cast<float>(t)));
	}
	if (!isInBounds()) {
		if (exploded && particleSystem) {
			if (particleSystem->getIsDone()) {
				for (size_t i = 0; i < holdingVector.size(); i++) {
					if (holdingVector[i].get() == this) {
						holdingVector.erase(holdingVector.begin() + i);
						break;
					}
				}
			}
		} else if (!exploded) {
			explode();
		}
	}
}

void Bullet::setAcceleration(sf::Vector2f a) {
	acceleration = a;
}

sf::RectangleShape& Bullet::getSprite() {
	return sprite;
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (!exploded) {
	target.draw(sprite);
	}
	if (particleSystem) {
		target.draw(*particleSystem);
	}
}

bool Bullet::isInBounds() const {
	return !(x <= 0 || x >= texture.getSize().x || y >= texture.getSize().y - 100 || y <= 50);
}

void Bullet::explode() {
	exploded = true;
	particleSystem = std::make_unique<ParticleExploder>(100, 360.0f, 0.0f, sf::Color{ 255, 100, 100 }, 2.0f, 100.0f, sf::Vector2f{ x, y });
	particleSystem->setAcceleration(sf::Vector2f{ 0, 40.81f });
}

float Bullet::getX() {
	return x;
}

float Bullet::getY() {
	return y;
}