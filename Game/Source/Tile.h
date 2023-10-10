#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Textures.h"

class Tile
{
public:
	enum TileType {
		NONE,
		WALL,
		FLOOR,
		DOOR,
		OBJECT
	} tileType;
	Tile();
	void setTilePosition(int y, int x);
	TileType getTileType();
	virtual sf::Sprite& getTileSprite();
	virtual ~Tile();
	sf::Sprite tileSprite;
	virtual void openPassage(Textures& textures);
	virtual void openDoor(Textures& textures);
	virtual void endDoor(Textures& textures);
	virtual bool isOpen();
	virtual bool isEnd();
	void setTileSprite(int y, int x, Textures& textures);
private:
	int tileY;
	int tileX;
};

class FloorTile: public Tile
{
public:
	FloorTile(Textures& textures);
};

class WallTile : public Tile
{
public:
	WallTile(Textures& textures);
	
};

class DoorTile : public Tile
{
public:
	DoorTile(Textures& textures);
	void openPassage(Textures& textures);
	void openDoor(Textures& textures);
	void endDoor(Textures& textures);
	bool isPassage();
	bool isOpen();
	bool isEnd();
private:
	bool passage;
	bool open;
	bool end;
};

class ObjectTile : public Tile
{
public:

	enum ObjectType {
		NONE,
		BOX_CLOSE,
		BOX_OPEN,
		TABLE1,
		TABLE2,
		OBJ1,
		CRATE1,
		CRATE2,
		COMPUTER1,
		COMPUTER2,
		TABLE3_LEFT,
		TABLE3_RIGHT,
		TABLE4,
		TABLE5,
		TABLE6_LEFT,
		TABLE6_RIGHT,
		OBJ2,
		CHAIR_DOWN,
		CHAIR_RIGHT,
		CHAIR_LEFT,
		CRATE3,
		TABLE7,
		BOOKCASE1,
		BOOKCASE2
	} objectType;
	ObjectTile();
	ObjectTile(Textures& textures, ObjectType type);
	ObjectType getObjectType();
};

