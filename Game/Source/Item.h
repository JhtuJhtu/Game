#pragma once
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Textures.h"

class Weapon
{
public:
	Weapon();
	void setFill();
	void setDamage(int dmg);
	void setRange(int rng);
	void setCost(int moveCost);
	void setWeaponSprite(int y, int x, Textures& textures);
	int getFill();
	int getDamage();
	int getRange();
	int getCost();
	void drawWeaponSprite(sf::RenderWindow& window, int i, std::ostringstream& string);
	sf::Sprite& getWeaponSprite();
private:
	int damage;
	int range;
	int cost;
	bool fill;
	sf::Sprite weaponSprite;
	sf::Text textDamage;
	sf::Text textRange;
	sf::Text textCost;
};

class Hammer : public Weapon 
{
public:
	Hammer();
	Hammer(Textures& textures);
};

class Rifle : public Weapon
{
public:
	Rifle();
	Rifle(Textures& textures);
};