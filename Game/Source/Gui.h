#pragma once
#include <sstream>

#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "Actor.h"

class Gui {
public:
	Gui(Textures& textures);
	void drawGui(sf::RenderWindow& window, std::shared_ptr<Player> player);
private:
	std::ostringstream string;
	sf::Text textHp;
	sf::Text textMovePoint;
	sf::Text textWeapon;
	sf::Text textStats;
};

class Target {
public:
	Target();
	void setTargetXY(int x, int y);
	void setTargetX(int x);
	void setTargetY(int y);
	void setTargetRange(int range);
	int getTargetX();
	int getTargetY();
	int getTargetRange();
	sf::Sprite& getTargetSprite();
	void drawTarget(sf::RenderWindow& window);
private:
	int targetX;
	int targetY;
	sf::Texture targetTexture;
	sf::Sprite targetSprite;
	int targetRange;
};