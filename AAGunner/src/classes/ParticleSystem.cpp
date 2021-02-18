#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(size_t count, float range, float angle, sf::Color color, float life, float speed) : particles{ count }, vertices{ sf::Points, count }, lifetime{ sf::seconds(life) }, position{ 0.0f, 0.0f }, acceleration{ 0.0f, 0.0f }, range{ range }, angle{ angle }, color{ color }, speed{ speed } {

}


ParticleSystem::~ParticleSystem() {
	particles.clear();
}

void ParticleSystem::setPosition(sf::Vector2f p) {
	position = p;
}

void ParticleSystem::setAcceleration(sf::Vector2f a) {
	acceleration = a;
}

void ParticleSystem::update(sf::Time elapsed) {
	for (size_t i = 0; i < particles.size(); i++) {
		auto& p = particles[i];
		p.lifetime -= elapsed;
		p.velocity += acceleration * elapsed.asSeconds();

		if (p.lifetime <= sf::Time::Zero) {
			resetParticle(i);
		}

		vertices[i].position += p.velocity * elapsed.asSeconds();
		vertices[i].color = p.color;
		auto ratio{ p.lifetime.asSeconds() / lifetime.asSeconds() };
		vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
	}
}

bool ParticleSystem::getIsDone() {
	return false;
}
void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(vertices, states);
}

void ParticleSystem::resetParticle(size_t index) {
	float a2{ (static_cast<float>(std::fmod(std::rand(), range)) + angle) * 3.14f / 180.0f };
	float s2{ (std::rand() % static_cast<int>(speed)) + 10.0f };
	particles[index].velocity = sf::Vector2f(std::cos(a2) * s2, std::sin(a2) * s2);
	particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + static_cast<int>(lifetime.asMilliseconds()) - 2000);
	particles[index].color = color;
	vertices[index].position = position;
	vertices[index].color = color;
}