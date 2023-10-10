#include "Room.h"

// Room

Room::Room() : map(0), roomSizeX(0), roomSizeY(0), roomTiles(NULL), roomType(NONE), roomObjects(NULL), action(true), turn(true) {
}

void Room::setMap(int m) {
	map = m;
}

void Room::setRoomTilesYX(int y, int x) {
	roomSizeY = y;
	roomSizeX = x;
	roomTiles.reserve(roomSizeY);
	roomObjects.reserve(roomSizeY);
	for (int y = 0; y < roomSizeY; y++) {
		roomTiles.push_back(std::vector<std::shared_ptr<Tile>>(roomSizeX));
		roomObjects.push_back(std::vector<std::shared_ptr<ObjectTile>>(roomSizeX));
		for (int x = 0; x < roomSizeX; x++) {
			roomObjects.at(y).at(x) = std::make_shared<ObjectTile>();
		}
	}
	
}

int Room::getMap() {
	return map;
}

int Room::getRoomSizeY() {
	return roomSizeY;
}

int Room::getRoomSizeX() {
	return roomSizeX;
}

std::shared_ptr<Tile> Room::getTile(int x, int y) {
	return roomTiles.at(x).at(y);
}

std::shared_ptr<ObjectTile> Room::getObject(int x, int y) {
	return roomObjects.at(x).at(y);
}

template<typename Type>
void Room::setRoomTile(int x, int y, Textures& textures) {
	roomTiles.at(x).at(y) = std::make_shared<Type>(textures);
}

void Room::setRoomObjects(int x, int y, Textures& textures, ObjectTile::ObjectType type) {
	roomObjects.at(x).at(y) = std::make_shared<ObjectTile>(textures, type);
}

void Room::setRoomDoor(int x, int y, Textures& textures) {
	roomTiles.at(x).at(y) = std::make_shared<DoorTile>(textures);
}

template<typename Type>
void Room::setRoomEnemy(int x, int y, Textures& textures) {
	roomEnemy.push_back(std::make_shared<Type>(x, y, textures));
}

void Room::setFloorAndWall(Textures& textures) {
	for (int y = 0; y < this->getRoomSizeY(); y++) {
		for (int x = 0; x < this->getRoomSizeX(); x++) {
			if (y == 0 || y == this->getRoomSizeY() - 1 || x == 0 || x == this->getRoomSizeX() - 1) {
				this->setRoomTile<WallTile>(y, x, textures);
			}
			else {
				this->setRoomTile<FloorTile>(y, x, textures);
			}
		}
	}
}

void Room::drawRoom(sf::RenderWindow& window, Textures& textures) {
	this->openRoomDoors(textures);
	for (int y = 0; y < roomSizeY; y++) {
		for (int x = 0; x < roomSizeX; x++) {
			roomTiles.at(y).at(x)->getTileSprite().setPosition(y * 32, x * 32);
			window.draw(roomTiles.at(y).at(x)->getTileSprite());
			if (roomObjects.at(y).at(x)->getTileType() == Tile::OBJECT) {
				roomObjects.at(y).at(x)->getTileSprite().setPosition(y * 32, x * 32);
				window.draw(roomObjects.at(y).at(x)->getTileSprite());
			}
		}
	}
	this->drawRoomEnemy(window);
}

void Room::drawRoomEnemy(sf::RenderWindow& window) {
	for (size_t i = 0; i < roomEnemy.size(); i++) {
		roomEnemy.at(i)->getActorSprite().setPosition(roomEnemy.at(i)->getActorX() * 32, (roomEnemy.at(i)->getActorY() - 1) * 32);
		window.draw(roomEnemy.at(i)->getActorSprite());
	}
}

void Room::openRoomDoors(Textures& textures) {
	if (this->isAliveEnemy(roomEnemy) == false) {
		this->getTile(9, 0)->openDoor(textures);
		this->getTile(9, 14)->openDoor(textures);
		if (this->getTile(0, 7)->getTileType() == Tile::DOOR) {
			this->getTile(0, 7)->openDoor(textures);
			this->getTile(19, 7)->openDoor(textures);
		}
	}
}

bool Room::isMovable(int y, int x) {
	if (this->getObject(y, x)->getObjectType() != ObjectTile::NONE) { return false; }
	if (this->getTile(y, x)->getTileType() == Tile::FLOOR) {
		for (size_t i = 0; i < roomEnemy.size(); i++) {
			if (roomEnemy.at(i)->getActorY() == x && roomEnemy.at(i)->getActorX() == y && roomEnemy.at(i)->getAlive() == true) { return false; }
		}
		return true;
	}
	return false;
}

bool Room::isAliveEnemy(std::vector<std::shared_ptr<Actor>>& enemy) {
	for (size_t i = 0; i < enemy.size(); i++) {
		if (enemy.at(i)->getAlive() == true) { return true; }
	}
	return false;
}

void Room::moveEnemy(std::shared_ptr<Player> player) {
	for (size_t i = 0; i < roomEnemy.size(); i++) {
		if (roomEnemy.at(i)->getAlive() == true) {
			turn = true;
			bool move = true;
			while (turn) {
				if (roomEnemy.at(i)->getCurMovePoint() - 1 >= 0) {
					int dx = player->getActorX() - roomEnemy.at(i)->getActorX();
					int dy = player->getActorY() - roomEnemy.at(i)->getActorY();


					int stepdx = (dx > 0 ? 1 : -1);
					int stepdy = (dy > 0 ? 1 : -1);

					float distance = sqrtf(dx * dx + dy * dy);

					if (distance > roomEnemy.at(i)->getWeapon().getRange()) {
						if (roomEnemy.at(i)->getCurMovePoint() - 1 >= 0 && move == true) {
							move = false;
							if (this->isMovable(roomEnemy.at(i)->getActorX(), roomEnemy.at(i)->getActorY() + stepdy) &&
								!roomEnemy.at(i)->isblocked(roomEnemy.at(i)->getActorX(), roomEnemy.at(i)->getActorY() + stepdy, player->getActorX(), player->getActorY())) {
								roomEnemy.at(i)->setActorY(roomEnemy.at(i)->getActorY() + stepdy);
								roomEnemy.at(i)->setCurMovePoint(roomEnemy.at(i)->getCurMovePoint() - 1);
								move = true;
							}

							if (this->isMovable(roomEnemy.at(i)->getActorX() + stepdx, roomEnemy.at(i)->getActorY()) &&
								!roomEnemy.at(i)->isblocked(roomEnemy.at(i)->getActorX() + stepdx, roomEnemy.at(i)->getActorY(), player->getActorX(), player->getActorY()) &&
								roomEnemy.at(i)->getCurMovePoint() - 1 >= 0) {
								roomEnemy.at(i)->setActorX(roomEnemy.at(i)->getActorX() + stepdx);
								roomEnemy.at(i)->setCurMovePoint(roomEnemy.at(i)->getCurMovePoint() - 1);
								move = true;
							}

						}
						else {
							turn = false;
							roomEnemy.at(i)->setCurMovePoint(roomEnemy.at(i)->getMaxMovePoint());
						}
					}
					else if (roomEnemy.at(i)->getCurMovePoint() - roomEnemy.at(i)->getWeapon().getCost() >= 0) {
						roomEnemy.at(i)->attack(player, roomEnemy.at(i)->getWeapon());
					}
					else {
						turn = false;
						roomEnemy.at(i)->setCurMovePoint(roomEnemy.at(i)->getMaxMovePoint());
					}
				}
				else {
					turn = false;
					roomEnemy.at(i)->setCurMovePoint(roomEnemy.at(i)->getMaxMovePoint());
				}

			}
		}
	}
}

int Room::moveActor(std::shared_ptr<Player> player, sf::Event& event, Target& target, sf::RenderWindow& window) {
	if (player->getGameStatus() != Player::TARGET) {
		if (this->isAliveEnemy(roomEnemy) == false) {
			player->setGameStatus(Player::FREE_TURN);
			player->setCurMovePoint(player->getMaxMovePoint());
		}
		else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			player->setGameStatus(Player::ENEMY_TURN);
		}
		else {
			player->setGameStatus(Player::PLAYER_TURN);
		}
	}

	if (player->getGameStatus() == Player::ENEMY_TURN && action == true) {
		this->moveEnemy(player);
		player->setGameStatus(Player::PLAYER_TURN);
		player->setCurMovePoint(player->getMaxMovePoint());
		action = false;
		return 0;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		player->setGameStatus(Player::NONE);
		player->setSelectedWeapon(-1);
		target.setTargetRange(0);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		if (player->getInventory(0).getFill()){
			player->setGameStatus(Player::TARGET);
			target.setTargetXY(player->getActorX(), player->getActorY());
			target.setTargetRange(player->getInventory(0).getRange());
			player->setSelectedWeapon(0);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		if (player->getInventory(1).getFill()) {
			player->setGameStatus(Player::TARGET);
			target.setTargetXY(player->getActorX(), player->getActorY());
			target.setTargetRange(player->getInventory(1).getRange());
			player->setSelectedWeapon(1);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
		if (player->getInventory(2).getFill()) {
			player->setGameStatus(Player::TARGET);
			target.setTargetXY(player->getActorX(), player->getActorY());
			target.setTargetRange(player->getInventory(2).getRange());
			player->setSelectedWeapon(2);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && player->getGameStatus() == Player::TARGET && action == true) {
		for (size_t i = 0; i < roomEnemy.size(); i++) {
			if (roomEnemy.at(i)->getActorY() == target.getTargetY() && roomEnemy.at(i)->getActorX() == target.getTargetX() && roomEnemy.at(i)->getAlive() == true) {
				player->attack(roomEnemy.at(i), player->getInventory(player->getSelectedWeapon()));
				action = false;
				return 0;
			}
		}
	}

	action = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		switch (player->getGameStatus())
		{
		case Player::FREE_TURN:

			if (this->getTile(player->getActorX(), player->getActorY() - 1)->getTileType() == Tile::DOOR) {
				if (this->getTile(player->getActorX(), player->getActorY() - 1)->isOpen() && !this->getTile(player->getActorX(), player->getActorY() - 1)->isEnd()) {
				
					player->setActorXY(9, 13);
					return 1;
				}
				else if (this->getTile(player->getActorX(), player->getActorY() - 1)->isEnd() && this->getTile(player->getActorX(), player->getActorY() - 1)->isOpen()) {
					return 5;
				}
			}
			if (this->isMovable(player->getActorX(), player->getActorY() - 1) == true) {
				player->setActorY(player->getActorY() - 1);
			}
			return 0;
			break;

		case Player::PLAYER_TURN:
			if (this->isMovable(player->getActorX(), player->getActorY() - 1) == true && player->getCurMovePoint() != 0) {
				player->setCurMovePoint(player->getCurMovePoint() - 1);
				player->setActorY(player->getActorY() - 1);
			}
			return 0;
			break;
		case Player::TARGET:
			if (target.getTargetY() - 1 >= 0 && target.getTargetY() > player->getActorY() - target.getTargetRange()) {
				target.setTargetY(target.getTargetY() - 1);
			}
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		switch (player->getGameStatus())
		{
		case Player::FREE_TURN:

			if (this->getTile(player->getActorX() - 1, player->getActorY())->getTileType() == Tile::DOOR) {
				if (this->getTile(player->getActorX() - 1, player->getActorY())->isOpen()) {
					player->setActorXY(18, 7);
					return 2;
				}
				
			}

			if (this->isMovable(player->getActorX() - 1, player->getActorY()) == true ) {
				player->setActorX(player->getActorX() - 1);
			}
			return 0;
			break;

		case Player::PLAYER_TURN:
			if (this->isMovable(player->getActorX() - 1, player->getActorY()) == true && player->getCurMovePoint() != 0) {
				player->setCurMovePoint(player->getCurMovePoint() - 1);
				player->setActorX(player->getActorX() - 1);
			}
			return 0;
			break;
		case Player::TARGET:
			if (target.getTargetX() - 1 >= 0 && target.getTargetX() > player->getActorX() - target.getTargetRange()) {
				target.setTargetX(target.getTargetX() - 1);
			}
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		switch (player->getGameStatus())
		{
		case Player::FREE_TURN:

			if (this->getTile(player->getActorX() + 1, player->getActorY())->getTileType() == Tile::DOOR) {
				if (this->getTile(player->getActorX() + 1, player->getActorY())->isOpen()) {
					player->setActorXY(1, 7);
					return 3;
				}
			}

			if (this->isMovable(player->getActorX() + 1, player->getActorY()) == true ) {
				player->setActorX(player->getActorX() + 1);
			}
			return 0;
			break;

		case Player::PLAYER_TURN:
			if (this->isMovable(player->getActorX() + 1, player->getActorY()) == true && player->getCurMovePoint() != 0) {
				player->setCurMovePoint(player->getCurMovePoint() - 1);
				player->setActorX(player->getActorX() + 1);
			}
			return 0;
			break;
		case Player::TARGET:
			if (target.getTargetX() + 1 < this->getRoomSizeY() && target.getTargetX() < player->getActorX() + target.getTargetRange()) {
				target.setTargetX(target.getTargetX() + 1);
			}
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		switch (player->getGameStatus())
		{
		case Player::FREE_TURN:

			if (this->getTile(player->getActorX(), player->getActorY() + 1)->getTileType() == Tile::DOOR) {
				if (this->getTile(player->getActorX(), player->getActorY() + 1)->isOpen()) {
					player->setActorXY(9, 1);
					return 4;
				}
			}
			if (this->isMovable(player->getActorX(), player->getActorY() + 1) == true) {
				player->setActorY(player->getActorY() + 1);
			}
			return 0;
			break;
		case Player::PLAYER_TURN:
			if (this->isMovable(player->getActorX(), player->getActorY() + 1) == true && player->getCurMovePoint() != 0) {
				player->setCurMovePoint(player->getCurMovePoint() - 1);
				player->setActorY(player->getActorY() + 1);
			}
			return 0;
			break;
		case Player::TARGET:
			if (target.getTargetY() + 1 < this->getRoomSizeX() && target.getTargetY() < player->getActorY() + target.getTargetRange()) {
				target.setTargetY(target.getTargetY() + 1);
			}
			break;
		}
	}	
	return 0;
}

//StartRoom

StartRoom::StartRoom(Textures& textures) {
	roomType = START;
	this->setRoomTilesYX(20, 15);
	this->setMap(8);
	this->setFloorAndWall(textures);
	this->setRoomDoor(9, 0, textures);
	this->setRoomDoor(9, 14, textures);
	std::uniform_int_distribution<int> objectDistrib(1, 2);
	auto seed = std::chrono::high_resolution_clock::now();
	std::mt19937 rnd(seed.time_since_epoch().count());
	this->setRoomObjects(3, 1, textures, ObjectTile::BOX_OPEN);
	this->setRoomObjects(14, 1, textures, ObjectTile::BOX_OPEN);
	this->setRoomObjects(11, 1, textures, ObjectTile::BOOKCASE2);
	this->setRoomObjects(12, 1, textures, ObjectTile::BOOKCASE2);
	this->setRoomObjects(13, 13, textures, ObjectTile::OBJ2);
	for (int y = 4; y <= 12; y++) {
		for (int x = 1; x <= 6; x++) {
			int object = objectDistrib(rnd);
			if (object == 1) {
				this->setRoomObjects(x, y, textures, ObjectTile::CRATE1);
			}
		}
	}
	for (int y = 4; y <= 10; y++) {
		for (int x = 16; x <= 18; x++) {
			this->setRoomObjects(x, y, textures, ObjectTile::CRATE2);
		}
	}
}

//StandartRoom

StandartRoom::StandartRoom(Textures& textures) {
	roomType = STANDART;
	this->setRoomTilesYX(20, 15);
	this->setMap(1);
	this->setFloorAndWall(textures);
	this->setRoomDoor(0, 7, textures);
	this->setRoomDoor(19, 7, textures);
	this->setRoomDoor(9, 0, textures);
	this->setRoomDoor(9, 14, textures);
	std::uniform_int_distribution<int> roomDistrib(1, 3);
	std::uniform_int_distribution<int> objectDistrib(1, 2);
	auto seed = std::chrono::high_resolution_clock::now();
	std::mt19937 rnd(seed.time_since_epoch().count());
	int room = roomDistrib(rnd);
	switch (room) {
	case 1:
		for (int x = 2; x <= 6; x++) {
			this->setRoomObjects(x, 1, textures, ObjectTile::BOOKCASE2);
		}

		for (int x = 12; x <= 17; x++) {
			this->setRoomObjects(x, 1, textures, ObjectTile::BOOKCASE2);
		}

		for (int x = 2; x <= 6; x++) {
			this->setRoomObjects(x, 5, textures, ObjectTile::BOOKCASE2);
		}

		for (int x = 12; x <= 17; x++) {
			this->setRoomObjects(x, 5, textures, ObjectTile::BOOKCASE2);
		}

		this->setRoomObjects(3, 9, textures, ObjectTile::TABLE7);
		this->setRoomObjects(4, 9, textures, ObjectTile::CHAIR_LEFT);

		this->setRoomObjects(16, 9, textures, ObjectTile::TABLE7);
		this->setRoomObjects(15, 9, textures, ObjectTile::CHAIR_RIGHT);

		this->setRoomObjects(3, 11, textures, ObjectTile::TABLE7);
		this->setRoomObjects(4, 11, textures, ObjectTile::CHAIR_LEFT);

		this->setRoomObjects(16, 11, textures, ObjectTile::TABLE7);
		this->setRoomObjects(15, 11, textures, ObjectTile::CHAIR_RIGHT);

		this->setRoomEnemy<RangeEnemy>(9, 6, textures);
		break;
	case 2:
		this->setRoomObjects(2, 2, textures, ObjectTile::CHAIR_DOWN);
		this->setRoomObjects(2, 3, textures, ObjectTile::TABLE5);

		this->setRoomObjects(6, 2, textures, ObjectTile::CHAIR_DOWN);
		this->setRoomObjects(6, 3, textures, ObjectTile::TABLE2);

		for (int y = 1; y <= 5; y += 2) {
			for (int x = 11; x <= 17; x += 2) {
				this->setRoomObjects(x, y, textures, ObjectTile::BOX_CLOSE);
			}
		}

		for (int y = 9; y <= 13; y++) {
			for (int x = 2; x <= 6; x++) {
				if (y != 11 && x != 4) { this->setRoomObjects(x, y, textures, ObjectTile::CRATE2); }
			}
		}

		for (int y = 9; y <= 13; y++) {
			for (int x = 13; x <= 17; x++) {
				if (y != 11 && x != 15) { this->setRoomObjects(x, y, textures, ObjectTile::CRATE1); }
			}
		}

		room = roomDistrib(rnd);
		if (room == 1) { this->setRoomEnemy<Enemy>(9, 3, textures); }
		else { this->setRoomEnemy<RangeEnemy>(6, 7, textures); }
	
		break;

	case 3:
		room = roomDistrib(rnd);
		if (room == 1) {

			this->setRoomObjects(11, 3, textures, ObjectTile::TABLE3_LEFT);
			this->setRoomObjects(12, 3, textures, ObjectTile::TABLE3_RIGHT);

			this->setRoomObjects(14, 3, textures, ObjectTile::TABLE3_LEFT);
			this->setRoomObjects(15, 3, textures, ObjectTile::TABLE3_RIGHT);

			this->setRoomObjects(17, 3, textures, ObjectTile::TABLE3_LEFT);
			this->setRoomObjects(18, 3, textures, ObjectTile::TABLE3_RIGHT);

			for (int x = 11; x <= 18; x++) {
				if (x != 13 && x != 16) { this->setRoomObjects(x, 2, textures, ObjectTile::CHAIR_DOWN); }
			}
		}
		else
		{
			for (int y = 2; y <= 4; y += 2) {
				for (int x = 11; x <= 17; x++) {
					if (x != 14) {
						room = roomDistrib(rnd);
						if (room == 1) { this->setRoomObjects(x, y, textures, ObjectTile::BOX_CLOSE); }
						else { this->setRoomObjects(x, y, textures, ObjectTile::BOX_OPEN); }
					}
				}
			}
		}
		room = roomDistrib(rnd);
		if (room == 1) {
			for (int y = 2; y <= 4; y += 2) {
				for (int x = 2; x <= 6; x += 2) {
					room = roomDistrib(rnd);
					if (room == 1) { this->setRoomObjects(x, y, textures, ObjectTile::COMPUTER1); }
					else { this->setRoomObjects(x, y, textures, ObjectTile::COMPUTER2); }
				}
			}
		}
		else {
			for (int y = 2; y <= 4; y += 2) {
				for (int x = 2; x <= 6; x += 2) {
					this->setRoomObjects(x, y, textures, ObjectTile::OBJ1);
				}
			}
		}

		room = roomDistrib(rnd);
		if (room == 1) {
			this->setRoomObjects(4, 10, textures, ObjectTile::OBJ2);
		}
		else {
			for (int y = 9; y <= 13; y += 2) {
				for (int x = 2; x <= 7; x++) {
					if (x != 5) {
						this->setRoomObjects(x, y, textures, ObjectTile::BOOKCASE2);
					}
				}
			}
		}

		room = roomDistrib(rnd);
		if (room == 1) {
			for (int y = 9; y <= 13; y += 2) {
				for (int x = 11; x <= 17; x++) {
					if (x != 14) {
						this->setRoomObjects(x, y, textures, ObjectTile::BOOKCASE1);
					}
				}
			}
		}
		else {
			this->setRoomObjects(11, 10, textures, ObjectTile::TABLE1);
			this->setRoomObjects(14, 10, textures, ObjectTile::TABLE1);
			this->setRoomObjects(17, 10, textures, ObjectTile::TABLE1);

			this->setRoomObjects(11, 12, textures, ObjectTile::TABLE2);
			this->setRoomObjects(14, 12, textures, ObjectTile::TABLE2);
			this->setRoomObjects(17, 12, textures, ObjectTile::TABLE2);
		}

		this->setRoomEnemy<Enemy>(8, 6, textures);
		this->setRoomEnemy<Enemy>(10, 6, textures);
		break;
	}	

}

//EndRoom

EndRoom::EndRoom(Textures& textures) {
	roomType = END;
	this->setRoomTilesYX(20, 15);
	this->setMap(9);
	this->setFloorAndWall(textures);

	this->setRoomDoor(0, 7, textures);
	this->setRoomDoor(19, 7, textures);
	this->setRoomDoor(9, 0, textures);
	this->getTile(9, 0)->endDoor(textures);
	this->setRoomDoor(9, 14, textures);

	this->setRoomObjects(2, 1, textures, ObjectTile::TABLE6_LEFT);
	this->setRoomObjects(3, 1, textures, ObjectTile::TABLE6_RIGHT);

	this->setRoomObjects(6, 1, textures, ObjectTile::TABLE6_LEFT);
	this->setRoomObjects(7, 1, textures, ObjectTile::TABLE6_RIGHT);

	this->setRoomObjects(11, 1, textures, ObjectTile::TABLE6_LEFT);
	this->setRoomObjects(12, 1, textures, ObjectTile::TABLE6_RIGHT);

	this->setRoomObjects(16, 1, textures, ObjectTile::TABLE6_LEFT);
	this->setRoomObjects(17, 1, textures, ObjectTile::TABLE6_RIGHT);

	this->setRoomObjects(4, 3, textures, ObjectTile::CHAIR_DOWN);
	this->setRoomObjects(5, 3, textures, ObjectTile::CHAIR_DOWN);
	this->setRoomObjects(4, 4, textures, ObjectTile::TABLE3_LEFT);
	this->setRoomObjects(5, 4, textures, ObjectTile::TABLE3_RIGHT);

	this->setRoomObjects(14, 3, textures, ObjectTile::CHAIR_DOWN);
	this->setRoomObjects(13, 4, textures, ObjectTile::TABLE3_LEFT);
	this->setRoomObjects(14, 4, textures, ObjectTile::TABLE1);
	this->setRoomObjects(15, 4, textures, ObjectTile::TABLE3_RIGHT);

	for (int y = 10; y <= 11; y++) {
		for (int x = 4; x <= 5; x++) {
			this->setRoomObjects(x, y, textures, ObjectTile::OBJ2);
		}
	}

	for (int y = 10; y <= 11; y++) {
		for (int x = 14; x <= 15; x++) {
			this->setRoomObjects(x, y, textures, ObjectTile::OBJ2);
		}
	}
	this->setRoomEnemy<BossEnemy>(9, 4, textures);
}