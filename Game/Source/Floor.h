#pragma once
#include <memory>
#include <random>
#include <chrono>

#include <SFML/Graphics.hpp>
#include "Room.h"


class Floor
{
public:
	Floor();
	void createFloor(Textures &textures);
	void drawFloorRoom(int y, int x, sf::RenderWindow& window, Textures& textures);
	std::shared_ptr<Room> getRoom(int y, int x);
private:
	static const int floorSizeY = 10;
	static const int floorSizeX = 10;
	int floorY;
	int floorX;
	std::shared_ptr<Room> floorRooms[floorSizeY][floorSizeX];
};

