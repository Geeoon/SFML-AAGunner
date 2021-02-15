#include <SFML/Graphics.hpp>
#include "classes/UIManager.h"
#include "classes/PlaneManager.h"
#include "classes/Player.h"

int main() {
	std::shared_ptr<Player> player;
	UIManager ui{800, 800, player};
	PlaneManager planeManager{10, ui.getTexture()};
	player = std::make_shared<Player>(static_cast<int>(ui.getTexture().getSize().x) / 2, static_cast<int>(ui.getTexture().getSize().y) - 100, ui.getTexture());
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