#include "Engine.h"

Engine::Engine() : currentRoomY(9), currentRoomX(4), gui(textures), floorNumber(1), nFloor(NULL) {
}

void Engine::startGame(sf::RenderWindow& window) {
	player = std::make_shared<Player>(9, 6, textures);
	nFloor = std::make_shared <Floor>();
	nFloor->createFloor(textures);
	nFloor->drawFloorRoom(currentRoomY, currentRoomX, window, textures);
	player->drawActor(window);
	nFloor->getRoom(currentRoomY, currentRoomX)->drawRoomEnemy(window);
	gui.drawGui(window, player);
	window.display();
}

void Engine::update(sf::RenderWindow& window, sf::Event event) {
	if (player->getGameStatus() != Player::VICTORY && player->getGameStatus() != Player::DEFEAT) {
		if (player->getHp() > 0) {
			window.clear();
			nFloor->drawFloorRoom(currentRoomY, currentRoomX, window, textures);
			player->drawActor(window);
			gui.drawGui(window, player);
			nFloor->getRoom(currentRoomY, currentRoomX)->drawRoomEnemy(window);
			if (player->getGameStatus() == Player::TARGET) {
				target.drawTarget(window);
			}
			switch (nFloor->getRoom(currentRoomY, currentRoomX)->moveActor(player, event, target, window))
			{
			case 1:
				nFloor->drawFloorRoom(currentRoomY--, currentRoomX, window, textures);
				break;

			case 2:
				nFloor->drawFloorRoom(currentRoomY, currentRoomX--, window, textures);
				break;

			case 3:
				nFloor->drawFloorRoom(currentRoomY, currentRoomX++, window, textures);
				break;

			case 4:
				nFloor->drawFloorRoom(currentRoomY++, currentRoomX, window, textures);
				break;
			case 5:
				if (floorNumber == 3) {
					player->setGameStatus(Player::VICTORY);
				}
				else {
					floorNumber++;
					nFloor.reset();
					nFloor = std::make_shared <Floor>();
					nFloor->createFloor(textures);
					currentRoomY = 9;
					currentRoomX = 4;
					player->setActorXY(9, 13);
					player->setHp(100);
				}
				break;
			}
			window.display();
		}
		else {
			player->setGameStatus(Player::DEFEAT);
		}
	}
	else {
		window.clear();
		sf::Text vinText;
		vinText.setFont(textures.getFont());
		vinText.setPosition(6 * 32, 1 * 32);
		vinText.setCharacterSize(18);
		vinText.setString("        The end \n Press Enter to restart");
		nFloor->drawFloorRoom(currentRoomY, currentRoomX, window, textures);
		player->drawActor(window);
		gui.drawGui(window, player);
		nFloor->getRoom(currentRoomY, currentRoomX)->drawRoomEnemy(window);
		window.draw(vinText);
		window.display();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			currentRoomY = 9;
			currentRoomX = 4;
			floorNumber = 1;
			this->startGame(window);
		}
	}
}
