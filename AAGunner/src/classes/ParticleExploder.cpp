#include "ParticleExploder.h"

ParticleExploder::ParticleExploder(size_t count, float range, float angle, sf::Color color, float life, float speed, sf::Vector2f pos) : ParticleSystem{ count, range, angle, color, life, speed } {
	position = pos;
	for (size_t i = 0; i < particles.size(); i++) {
		resetParticle(i);
	}
}

ParticleExploder::ParticleExploder(size_t count, float range, float angle, sf::Color color, float life, float speed, std::vector<ParticleExploder>* holdingVector, sf::Vector2f pos) : ParticleSystem{ count, range, angle, color, life, speed }, holdingVector{ holdingVector } {
	position = pos;
	for (size_t i = 0; i < particles.size(); i++) {
		resetParticle(i);
	}
}

void ParticleExploder::update(sf::Time elapsed) {
	bool allUsed = true;
	
	for (size_t i = 0; i < particles.size(); i++) {
		auto& p{ particles[i] };
		p.lifetime -= elapsed;
		p.velocity += acceleration;

		if (p.lifetime > sf::Time::Zero && allUsed) {
			allUsed = false;
		}

		vertices[i].position += p.velocity * elapsed.asSeconds();
		vertices[i].color = p.color;
		auto ratio{ p.lifetime.asSeconds() / lifetime.asSeconds() };
		if (ratio >= 0) {
			vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
		} else {
			vertices[i].color.a = 0;
			p.lifetime = sf::seconds(0);
		}
	}
	
	if (allUsed && holdingVector) {
		for (size_t i = 0; i < holdingVector->size(); i++) {
			auto& particleSystem = (*holdingVector)[i];
			if (&particleSystem == this) {
				holdingVector->erase(holdingVector->begin() + i);
				break;
			}
		}
	}
}