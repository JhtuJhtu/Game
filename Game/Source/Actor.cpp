#pragma once
#include "Actor.h"

//Actor

Actor::Actor() : actorX(0), actorY(0), curMovePoint(0), maxMovePoint(0), alive(true), hp(0) {
}

void Actor::setActorXY(int x, int y) {
	actorX = x;
	actorY = y;
}

void Actor::setActorX(int x) {
	actorX = x;
}

void Actor::setActorY(int y) {
	actorY = y;
}

void Actor::setActorSprite(int y, int x, Textures& textures) {
	actorSprite.setTexture(textures.getActorTexture());
	actorSprite.setTextureRect(sf::IntRect(x * 32, y * 32, 32, 64));
}

void Actor::setMaxMovePoint(int point) {
	maxMovePoint = point;
}

void Actor::setCurMovePoint(int point) {
	curMovePoint = point;
}

void Actor::setHp(int point) {
	hp = point;
}

void Actor::setAlive(bool live) {
	alive = live;
}

int Actor::getHp() {
	return hp;
}

int Actor::getMaxMovePoint() {
	return maxMovePoint;
}

int Actor::getCurMovePoint() {
	return curMovePoint;
}

int Actor::getActorX() {
	return actorX;
}

int Actor::getActorY() {
	return actorY;
}

bool Actor::getAlive() {
	return alive;
}

sf::Sprite& Actor::getActorSprite() {
	return actorSprite;
}
Weapon Actor::getWeapon() {
	Weapon none;
	return none;
}



void Actor::changeActorSprite(int y, int x) {
	actorSprite.setTextureRect(sf::IntRect(x * 32, y * 32, 32, 32));
}

void Actor::drawActor(sf::RenderWindow& window) {
	this->getActorSprite().setPosition(actorX * 32, (actorY - 1) * 32);
	window.draw(this->getActorSprite());
}

void Actor::destroyed() {
	this->setAlive(false);
	this->changeActorSprite(0, 0);
}

void Actor::attack(std::shared_ptr<Actor> target, Weapon weapon) {
	if (this->getCurMovePoint() - weapon.getCost() >= 0) {
		this->setCurMovePoint(this->getCurMovePoint() - weapon.getCost());
		target->setHp(target->getHp() - weapon.getDamage());
		if (target->getHp() <= 0) {
			target->destroyed();
		}
	}
}

bool Actor::isblocked(int x1, int y1, int x2, int y2) {
	if (x1 == x2 && y1 == y2) {
		return true;
	}
	else {
		return false;
	}
}

//Player

Player::Player(int x, int y, Textures& textures) : gameStatus(NONE) {
	Hammer hammer(textures);
	Rifle rifle(textures);
	this->setActorXY(x, y);
	this->setActorSprite(0, 0, textures);
	this->setMaxMovePoint(10);
	this->setCurMovePoint(this->getMaxMovePoint());
	this->setHp(100);
	this->setInventory(hammer);
	this->setInventory(rifle);
}

void Player::setGameStatus(Player::GameStatus status) {
	gameStatus = status;
}

void Player::setInventory(Weapon newItem) {
	for (int i = 0; i < 3; i++) {
		if (!inventory[i].getFill()) {
			inventory[i] = newItem;
			break;
		}
	}
}

void Player::setSelectedWeapon(int select) {
	selectedWeapon = select;
}

Player::GameStatus Player::getGameStatus() {
	return gameStatus;
}

Weapon Player::getInventory(int item) {
	return inventory[item];
}

int Player::getSelectedWeapon() {
	return selectedWeapon;
}

//Enemy

Enemy::Enemy(int x, int y, Textures& textures) : turn(false) {
	this->setActorXY(x, y);
	this->setActorSprite(0, 1, textures);
	this->setMaxMovePoint(6);
	this->setCurMovePoint(this->getMaxMovePoint());
	this->setHp(50);
}

Weapon Enemy::getWeapon() {
	return hammer;
}

//RangeEnemy

RangeEnemy::RangeEnemy(int x, int y, Textures& textures) : turn(false) {
	this->setActorXY(x, y);
	this->setActorSprite(0, 3, textures);
	this->setMaxMovePoint(6);
	this->setCurMovePoint(this->getMaxMovePoint());
	this->setHp(20);
}

Weapon RangeEnemy::getWeapon() {
	return rifle;
}

//BossEnemy

BossEnemy::BossEnemy(int x, int y, Textures& textures) : turn(false) {
	this->setActorXY(x, y);
	this->setActorSprite(0, 2, textures);
	this->setMaxMovePoint(8);
	this->setCurMovePoint(this->getMaxMovePoint());
	this->setHp(100);
}

Weapon BossEnemy::getWeapon() {
	return hammer;
}