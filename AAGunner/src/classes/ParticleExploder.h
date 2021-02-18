#pragma once
#include "ParticleSystem.h"

class ParticleExploder : public ParticleSystem {
public:
	ParticleExploder(size_t count, float range, float angle, sf::Color color, float life, float speed, sf::Vector2f pos);
	ParticleExploder(size_t count, float range, float angle, sf::Color color, float life, float speed, std::vector<std::unique_ptr<ParticleSystem>>* holdingVector, sf::Vector2f pos);
	virtual void update(sf::Time elapsed) override;
	virtual bool getIsDone() override;

private:
	std::vector<std::unique_ptr<ParticleSystem>>* holdingVector = nullptr;
	bool isDone;
};