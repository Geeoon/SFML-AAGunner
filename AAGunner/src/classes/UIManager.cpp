#include "UIManager.h"

UIManager::UIManager(std::shared_ptr<Player>& player) : player{ player } {
	window.create(sf::VideoMode::getFullscreenModes()[0], "AA Gunner", sf::Style::Fullscreen);
	texture.create(window.getSize().x, window.getSize().y);
	window.setFramerateLimit(120);
	sf::Cursor c;
	if (c.loadFromSystem(sf::Cursor::Cross)) {
		window.setMouseCursor(c);
	}
}

UIManager::UIManager(unsigned int x, unsigned int y, std::shared_ptr<Player>& player) : player{ player } {
	window.create(sf::VideoMode{ x, y }, "AA Gunner", sf::Style::Close);
	texture.create(window.getSize().x, window.getSize().y);
	window.setFramerateLimit(120);
	sf::Cursor c;
	if (c.loadFromSystem(sf::Cursor::Cross)) {
		window.setMouseCursor(c);
	}
}

bool UIManager::isOpen() {
	return window.isOpen();
}

void UIManager::update() {
	sf::Event e;
	while (window.pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			window.close();
		} else if (e.type == sf::Event::MouseButtonPressed) {
			player->fire();
		}
	}
	window.clear();
	texture.clear();
}

void UIManager::draw(const sf::Drawable& d) {
	texture.draw(d);
}

void UIManager::display() {
	texture.display();
	window.draw(sf::Sprite{ texture.getTexture() });
	window.display();
}

sf::RenderTexture& UIManager::getTexture() {
	return texture;
}

sf::RenderWindow& UIManager::getWindow() {
	return window;
}