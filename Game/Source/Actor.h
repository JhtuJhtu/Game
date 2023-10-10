#pragma once
#include <vector>

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Item.h"

class Actor {
public:
	Actor();
	void setActorXY(int x, int y);
	void setActorX(int x);
	void setActorY(int y);
	void setActorSprite(int y, int x, Textures& textures);
	void setMaxMovePoint(int point);
	void setCurMovePoint(int point);
	void setHp(int point);
	void setAlive(bool live);
	int getHp();
	int getMaxMovePoint();
	int getCurMovePoint();
	int getActorX();
	int getActorY();
	bool getAlive();
	sf::Sprite& getActorSprite();
	virtual Weapon getWeapon();
	void changeActorSprite(int y, int x);
	void drawActor(sf::RenderWindow& window);
	void destroyed();
	void attack(std::shared_ptr<Actor> target, Weapon weapon);
	bool isblocked(int x, int y, int x2, int y2);
private:
	int actorX;
	int actorY;
	int maxMovePoint;
	int curMovePoint;
	int hp;
	bool alive;
	sf::Sprite actorSprite;
};

class Player : public Actor {
public:
	enum GameStatus {
		NONE,
		FREE_TURN,
		PLAYER_TURN,
		ENEMY_TURN,
		TARGET,
		VICTORY,
		DEFEAT
	} gameStatus;
	Player(int x, int y, Textures& textures);
	void setGameStatus(GameStatus status);
	void setInventory(Weapon newItem);
	void setSelectedWeapon(int select);
	GameStatus getGameStatus();
	Weapon getInventory(int item);
	int getSelectedWeapon();
private: 
	Weapon inventory[3];
	int selectedWeapon;
};

class Enemy : public Actor {
public:
	Enemy(int x, int y, Textures& textures);
	Weapon getWeapon();
private:
	bool turn;
	Hammer hammer;
};

class RangeEnemy : public Actor {
public:
	RangeEnemy(int x, int y, Textures& textures);
	Weapon getWeapon();
private:
	bool turn;
	Rifle rifle;
};

class BossEnemy : public Actor {
public:
	BossEnemy(int x, int y, Textures& textures);
	Weapon getWeapon();
private:
	bool turn;
	Hammer hammer;
};