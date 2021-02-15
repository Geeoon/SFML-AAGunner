#pragma once
#include "ParticleSystem.h"

class ParticleExploder : public ParticleSystem {
public:
	ParticleExploder(size_t count, float range, float angle, sf::Color color, float life, float speed, sf::Vector2f pos);
	ParticleExploder(size_t count, float range, float angle, sf::Color color, float life, float speed, std::vector<ParticleExploder>* holdingVector, sf::Vector2f pos);
	virtual void update(sf::Time elapsed) override;

private:
	std::vector<ParticleExploder>* holdingVector = nullptr;
};