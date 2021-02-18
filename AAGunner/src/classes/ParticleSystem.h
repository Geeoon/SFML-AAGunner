#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class ParticleSystem : public sf::Drawable, public sf::Transformable {
public:
	ParticleSystem(size_t count, float range, float angle, sf::Color color, float life, float speed);
	~ParticleSystem();
	void setPosition(sf::Vector2f p);
	void setAcceleration(sf::Vector2f a);
	virtual void update(sf::Time elapsed);
	virtual bool getIsDone();

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	struct Particle {
		sf::Vector2f velocity;
		sf::Time lifetime;
		sf::Color color;
	};
	void resetParticle(size_t index);
	std::vector<Particle> particles;
	sf::VertexArray vertices;
	sf::Vector2f position;
	sf::Vector2f acceleration;
	sf::Time lifetime;
	sf::Color color;
	float range, angle, speed;

private:
};