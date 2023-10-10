#include "Floor.h"

Floor::Floor() : floorX(4), floorY(floorSizeY - 1), floorRooms() {
}

void Floor::createFloor(Textures& textures) {
	int oldFloorX = 0;
	int oldFloorY = 0;
	int roomsLeft = 1;
	bool end = false;
	enum Side {
		UP = 1,
		DOWN = 2,
		LEFT = 3,
		RIGHT = 4
	} roomSide = UP;
	
	Room::RoomType roomType = Room::NONE;

	for (int y = 0; y < floorSizeY; y++) {
		for (int x = 0; x < floorSizeX; x++) {
			floorRooms[y][x] = std::make_shared<Room>();
		}
	}

	std::uniform_int_distribution<int> roomDistrib(1, 3);
	std::uniform_int_distribution<int> turnDistrib(1, 2);
	auto seed = std::chrono::high_resolution_clock::now();
	std::mt19937 rnd(seed.time_since_epoch().count());
	floorRooms[floorY][floorX] = std::make_shared<StartRoom>(textures);
	floorY--;
	floorRooms[floorY][floorX] = std::make_shared<StandartRoom>(textures);

	while (!end) {
		int nextRoom = roomDistrib(rnd);
		if (nextRoom == 1) {
			roomSide = LEFT;
		}
		else if (nextRoom == 2) {
			roomSide = RIGHT;
		}
		else if (nextRoom == 3) {
			roomSide = UP;
		}
		switch (roomSide)
		{
		case UP:
			if (floorRooms[floorY - 1][floorX]->getMap() == 0) {
				floorY--;
				roomsLeft--;
				if (roomsLeft == 0) {
					floorRooms[floorY][floorX] = std::make_shared<EndRoom>(textures);
					end = true;
				}
				else {
					floorRooms[floorY][floorX] = std::make_shared<StandartRoom>(textures);
				}
			}
			break;
		case LEFT:
			if (floorX - 1 >= 0 && floorRooms[floorY][floorX - 1]->getMap() == 0) {
				oldFloorX = floorX;
				oldFloorY = floorY;
				roomsLeft--;
				floorX--;
				if (roomsLeft == 0) {
					floorRooms[floorY][floorX] = std::make_shared<EndRoom>(textures);
					end = true;
				}
				else {
					floorRooms[floorY][floorX] = std::make_shared<StandartRoom>(textures);
					nextRoom = turnDistrib(rnd);
					if (nextRoom == 1) {
						floorX = oldFloorX;
					}
				}
			}
			break;
		case RIGHT:
			if (floorX + 1 <= floorSizeX - 1 && floorRooms[floorY][floorX + 1]->getMap() == 0) {
				oldFloorX = floorX;
				oldFloorY = floorY;
				floorX++;
				roomsLeft--;
				if (roomsLeft == 0) {
					floorRooms[floorY][floorX] = std::make_shared<EndRoom>(textures);;
					end = true;
				}
				else {
					floorRooms[floorY][floorX] = std::make_shared<StandartRoom>(textures);;

					nextRoom = turnDistrib(rnd);
					if (nextRoom == 1) {
						floorX = oldFloorX;
					}
				}
			}
			break;
		}
	}
	for (int y = 0; y < floorSizeY; y++) {
		for (int x = 0; x < floorSizeX; x++) {
			if (floorRooms[y][x]->getMap() != 0) {
				if (y - 1 >= 0) {
					if (floorRooms[y - 1][x]->getMap() != 0) {
						floorRooms[y][x]->getTile(9, 0)->openPassage(textures);
					}
				}
				if (y + 1 < floorSizeY) {
					if (floorRooms[y + 1][x]->getMap() != 0) {
						floorRooms[y][x]->getTile(9, 14)->openPassage(textures);
					}
				}
				if (x - 1 >= 0) {
					if (floorRooms[y][x - 1]->getMap() != 0) {
						floorRooms[y][x]->getTile(0, 7)->openPassage(textures);
					}
				}
				if (x + 1 < floorSizeX) {
					if (floorRooms[y][x + 1]->getMap() != 0) {
						floorRooms[y][x]->getTile(19, 7)->openPassage(textures);
					}
				}
			}
			if (floorRooms[y][x]->getMap() == 9) {
				floorRooms[y][x]->getTile(9, 0)->openPassage(textures);
				floorRooms[y][x]->getTile(9, 0)->endDoor(textures);
			}
		}
	}
}

void Floor::drawFloorRoom(int y, int x, sf::RenderWindow& window, Textures& textures) {
	floorRooms[y][x]->drawRoom(window, textures);
}

std::shared_ptr<Room> Floor::getRoom(int y, int x) {
	return floorRooms[y][x];
}