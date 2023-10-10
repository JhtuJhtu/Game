#pragma once
#include <memory>
#include <random>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <vector>
#include "Tile.h"
#include "Textures.h"
#include "Actor.h"
#include "Gui.h"

class Room 
{
public:
	enum RoomType {
		NONE,
		START,
		END,
		STANDART
	} roomType;
	Room();
	void setMap(int m);
	void setRoomTilesYX(int y, int x);
	int getMap();
	int getRoomSizeY();
	int getRoomSizeX();
	std::shared_ptr<Tile> getTile(int x, int y);
	std::shared_ptr<ObjectTile> getObject(int x, int y);
	template<typename Type>
	void setRoomTile(int x, int y, Textures& textures);
	void setRoomObjects(int x, int y, Textures& textures, ObjectTile::ObjectType type);
	void setRoomDoor(int x, int y, Textures& textures);
	template<typename Type>
	void setRoomEnemy(int x, int y, Textures& textures);
	void setFloorAndWall(Textures& textures);
	void drawRoom(sf::RenderWindow& window, Textures& textures);
	void drawRoomEnemy(sf::RenderWindow& window);
	void openRoomDoors(Textures& textures);
	bool isMovable(int y, int x);
	bool isAliveEnemy(std::vector<std::shared_ptr<Actor>>& enemy);
	void moveEnemy(std::shared_ptr<Player> player);
	int moveActor(std::shared_ptr<Player> player, sf::Event& event, Target& target, sf::RenderWindow& window);
private:
	int roomSizeY;
	int roomSizeX;
	std::vector<std::vector<std::shared_ptr<Tile>>> roomTiles;
	std::vector<std::vector<std::shared_ptr<ObjectTile>>> roomObjects;
	std::vector <std::shared_ptr<Actor>> roomEnemy;
	int map;
	bool action;
	bool turn;
 };

class StartRoom : public Room
{
public:
	StartRoom(Textures& textures);
};

class StandartRoom : public Room
{
public: 
	StandartRoom(Textures& textures);
};

class EndRoom : public Room
{
public:
	EndRoom(Textures& textures);
};