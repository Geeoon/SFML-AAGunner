#include "PlaneManager.h"

PlaneManager::PlaneManager(size_t num, const sf::RenderTexture& t) : planes{ num }, xBound{ static_cast<int>(t.getSize().x) }, yBound{ static_cast<int>(t.getSize().y) } {
	srand(static_cast<unsigned int>(time(0)));
	for (size_t i = 0; i < planes.size(); i++) {
		auto x = static_cast<float>(std::rand() % xBound);
		auto y = static_cast<float>(std::rand() % 50 + 25);
		auto s = static_cast<float>(std::rand() % 200 + 100);
		planes[i] = std::make_unique<Plane>(x, y, s);
		if (std::rand() % 2 == 1) {
			planes[i]->reflect();
		}
	}
	texture.create(xBound, yBound);
	clock.restart();
}

void PlaneManager::update() {
	for (size_t i = 0; i < planes.size(); i++) {
		double deltaT = clock.getElapsedTime().asSeconds();
		if (deltaT > 0.1) {
			deltaT = 0.1;
		}
		planes[i]->update(deltaT);
		if (planes[i]->getX() > xBound + 100 || planes[i]->getX() < -100) {
			planes[i]->reflect();
		}
	}
	clock.restart();
}

sf::Sprite PlaneManager::getSprite() {
	texture.clear(sf::Color::Transparent);
	for (size_t i = 0; i < planes.size(); i++) {
		texture.draw(planes[i]->getSprite());
	}
	texture.display();
	return sf::Sprite{ texture.getTexture() };
}