#include "Tile.h"


//tile

Tile::Tile() : tileY(0), tileX(0), tileType(NONE) {
}

Tile::~Tile() {
}

sf::Sprite& Tile::getTileSprite() {
	return tileSprite;
}

void Tile::setTilePosition(int y, int x) {
	tileY = y;
	tileX = x;
	tileSprite.setPosition(y, x);
}

Tile::TileType Tile::getTileType() {
	return tileType;
}

void Tile::openPassage(Textures& textures) {
	std::cout << "Can't 'openPassage': It's not a door";
	ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

void Tile::openDoor(Textures& textures) {
	std::cout << "Can't 'openDoor': It's not a door";
	ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

void Tile::endDoor(Textures& textures) {
	std::cout << "Can't 'endDoor': It's not a door";
	ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

bool Tile::isOpen() {
	std::cout << "Can't 'isOpen': It's not a door";
	ShowWindow(::GetConsoleWindow(), SW_SHOW);
	return false;
}

bool Tile::isEnd() {
	std::cout << "Can't 'isEnd': It's not a door";
	ShowWindow(::GetConsoleWindow(), SW_SHOW);
	return false;
}

void Tile::setTileSprite(int y, int x, Textures& textures) {
	tileSprite.setTexture(textures.getTileTexture());
	tileSprite.setTextureRect(sf::IntRect(x * 32, y * 32, 32, 32));
}

//floorTile

FloorTile::FloorTile(Textures& textures) {
	this->setTileSprite(0,2,textures);
	tileType = FLOOR;
}

//wallTile

WallTile::WallTile(Textures& textures) {
		this->setTileSprite(0, 1, textures);
	tileType = WALL;
}

//doorTile

DoorTile::DoorTile(Textures& textures) : open(false), end(false), passage(false){
	this->setTileSprite(0, 3, textures);
	tileType = DOOR;
}

void DoorTile::openPassage(Textures& textures) {
	passage = true;
}

void DoorTile::openDoor(Textures& textures) {
	if (this->isPassage() || this->isEnd()) {
		this->setTileSprite(0, 4, textures);
		open = true;
	}
}

void DoorTile::endDoor(Textures& textures) {
	end = true;
}

bool DoorTile::isPassage() {
	return passage;
}

bool DoorTile::isOpen() {
	return open;
}


bool DoorTile::isEnd() {
	return end;
}

//objectTile

ObjectTile::ObjectTile() : objectType(NONE) {
	tileType = Tile::NONE;
}

ObjectTile::ObjectTile(Textures& textures, ObjectType type) {
	tileType = OBJECT;
	objectType = type;
	
	switch (objectType)
	{
	case ObjectTile::BOX_CLOSE:
		this->setTileSprite(0, 5, textures);
		break;
	case ObjectTile::BOX_OPEN:
		this->setTileSprite(0, 6, textures);
		break;
	case ObjectTile::TABLE1:
		this->setTileSprite(1, 0, textures);
		break;
	case ObjectTile::TABLE2:
		this->setTileSprite(1, 1, textures);
		break;
	case ObjectTile::OBJ1:
		this->setTileSprite(1, 2, textures);
		break;
	case ObjectTile::CRATE1:
		this->setTileSprite(1, 3, textures);
		break;
	case ObjectTile::CRATE2:
		this->setTileSprite(1, 4, textures);
		break;
	case ObjectTile::COMPUTER1:
		this->setTileSprite(1, 5, textures);
		break;
	case ObjectTile::COMPUTER2:
		this->setTileSprite(1, 6, textures);
		break;
	case ObjectTile::TABLE3_LEFT:
		this->setTileSprite(2, 0, textures);
		break;
	case ObjectTile::TABLE3_RIGHT:
		this->setTileSprite(2, 1, textures);
		break;
	case ObjectTile::TABLE4:
		this->setTileSprite(2, 2, textures);
		break;
	case ObjectTile::TABLE5:
		this->setTileSprite(2, 3, textures);
		break;
	case ObjectTile::TABLE6_LEFT:
		this->setTileSprite(2, 4, textures);
		break;
	case ObjectTile::TABLE6_RIGHT:
		this->setTileSprite(2, 5, textures);
		break;
	case ObjectTile::OBJ2:
		this->setTileSprite(2, 6, textures);
		break;
	case ObjectTile::CHAIR_DOWN:
		this->setTileSprite(3, 0, textures);
		break;
	case ObjectTile::CHAIR_RIGHT:
		this->setTileSprite(3, 1, textures);
		break;
	case ObjectTile::CHAIR_LEFT:
		this->setTileSprite(3, 2, textures);
		break;
	case ObjectTile::CRATE3:
		this->setTileSprite(3, 3, textures);
		break;
	case ObjectTile::TABLE7:
		this->setTileSprite(3, 4, textures);
		break;
	case ObjectTile::BOOKCASE1:
		this->setTileSprite(3, 5, textures);
		break;
	case ObjectTile::BOOKCASE2:
		this->setTileSprite(3, 6, textures);
		break;
	default:
		tileType = Tile::NONE;
		objectType = NONE;
		break;
	}
}

ObjectTile::ObjectType ObjectTile::getObjectType() {
	return objectType;
}