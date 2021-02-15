#include "Bullet.h"

Bullet::Bullet(float x, float y, float heading, double velocity, sf::RenderTexture& texture, std::vector<std::shared_ptr<Bullet>>& holdingVector) : x{ x }, y{ y }, heading{ heading }, velocity{ velocity }, texture{ texture }, holdingVector{ holdingVector } {
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
	x += sinf(heading * 3.1415f / 180.0f) * static_cast<float>(velocity * t);
	y -= cosf(heading * 3.1415f / 180.0f) * static_cast<float>(velocity * t);
	sprite.setPosition(x, y);
	if (!isInBounds() || timer.getElapsedTime().asSeconds() > static_cast<float>(static_cast<double>(texture.getSize().y) * 0.75 / velocity)) {
		for (size_t i = 0; i < holdingVector.size(); i++) {
			if (holdingVector[i].get() == this) {
				holdingVector.erase(holdingVector.begin() + i);
				break;
			}
		}
	}
}

sf::RectangleShape& Bullet::getSprite() {
	return sprite;
}

bool Bullet::isInBounds() {
	return !(x < -100 || x > texture.getSize().x + 100 || y > texture.getSize().y + 100 || y < -100);
}