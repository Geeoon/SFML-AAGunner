#include "Player.h"

Player::Player(int x, int y, sf::RenderTexture& texture) : x{ x }, y{ y }, angle{ 0 }, texture{ texture } {
	base.setFillColor(sf::Color::Black);
	base.setSize(sf::Vector2f{ 40, 20 });
	base.setOutlineColor(sf::Color{ 0, 255, 65 });
	base.setOutlineThickness(2);
	base.setOrigin(base.getLocalBounds().width / 2.0f, base.getLocalBounds().height / 2.0f);
	base.setPosition(static_cast<float>(x), static_cast<float>(y));

	cannon.setFillColor(sf::Color::Black);
	cannon.setSize(sf::Vector2f{ 3, 40 });
	cannon.setOutlineColor(sf::Color{ 0, 255, 65 });
	cannon.setOutlineThickness(2);
	cannon.setOrigin(cannon.getLocalBounds().width / 2.0f - 1.0f, cannon.getLocalBounds().height);
	cannon.setPosition(static_cast<float>(x), static_cast<float>(y));

	bullets.resize(0);
	//particleSystems.resize(0);
	clock.restart();
}

void Player::draw() {
	texture.draw(cannon);
	texture.draw(base);
	for (const auto& system : particleSystems) {
		texture.draw(system);
	}

	for (size_t i = 0; i < bullets.size(); i++) {
		texture.draw(bullets[i]->getSprite());
	}
}

void Player::update(const sf::RenderWindow& w) {
	double dx = sf::Mouse::getPosition(w).x;
	double dy = sf::Mouse::getPosition(w).y;
	float dt = clock.getElapsedTime().asSeconds();
	clock.restart();
	for (size_t i = 0; i < particleSystems.size(); i++) {
		if (&particleSystems[i]) {
			particleSystems[i].update(sf::seconds(dt));
		}
	}
	if (dt > 0.1f) {
		dt = 0.1f;
	}
	angle = atan2(dx - x, y - dy) * 180.0 / 3.1415;
	if (angle < -50) {
		angle = -50;
	} else if (angle > 50) {
		angle = 50;
	}
	cannon.setRotation(static_cast<float>(angle));
	for (size_t i = 0; i < bullets.size(); i++) {
		bullets[i]->update(static_cast<float>(dt));
	}
}

void Player::fire() {
	particleSystems.push_back(ParticleExploder{ 1000, 10, static_cast<float>(angle - 90.0), sf::Color{ 255, 65, 65 }, 0.5f, 350, &particleSystems, sf::Vector2f{ static_cast<float>(x) + cannon.getSize().y * sinf(static_cast<float>(angle * 3.1415 / 180.0)), static_cast<float>(y) - cannon.getSize().y * cosf(static_cast<float>(angle * 3.1415 / 180.0)) } });
	particleSystems.back().setAcceleration(sf::Vector2f{ 0.0f, 1.0f });
	bullets.push_back(std::make_unique<Bullet>(static_cast<float>(x) + cannon.getSize().y * sinf(static_cast<float>(angle * 3.1415 / 180.0)), static_cast<float>(y) - cannon.getSize().y * cosf(static_cast<float>(angle * 3.1415 / 180.0)), static_cast<float>(angle), 500.0, texture, bullets));
}