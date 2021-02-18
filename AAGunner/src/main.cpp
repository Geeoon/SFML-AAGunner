#include <SFML/Graphics.hpp>
#include "classes/UIManager.h"
#include "classes/PlaneManager.h"
#include "classes/Player.h"

int main() {
	std::unique_ptr<Player> player;
	UIManager ui{800, 800, player};
	player = std::make_unique<Player>(static_cast<int>(ui.getTexture().getSize().x) / 2, static_cast<int>(ui.getTexture().getSize().y) - 100, ui.getTexture());
	PlaneManager planeManager{10, player, ui.getTexture()};
	while (ui.isOpen()) {
		planeManager.update();
		player->update(ui.getWindow());
		ui.update();
		ui.draw(planeManager.getSprite());
		player->draw();
		ui.display();
	}
	return 0;
}