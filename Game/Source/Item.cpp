#include "Item.h"

//Weapon

Weapon::Weapon() : damage(0), range(0), cost(0), fill(false) {
}

void Weapon::setFill() {
	fill = true;
}

void Weapon::setDamage(int dmg) {
	damage = dmg;
}

void Weapon::setRange(int rng) {
	range = rng;
}

void Weapon::setCost(int moveCost) {
	cost = moveCost;
}

void Weapon::setWeaponSprite(int y, int x, Textures& textures) {

	weaponSprite.setTexture(textures.getWeaponTexture());
	weaponSprite.setTextureRect(sf::IntRect(x * 32, y * 32, 32, 32));

	textDamage.setFont(textures.getFont());
	textRange.setFont(textures.getFont());
	textCost.setFont(textures.getFont());

	textDamage.setCharacterSize(14);
	textRange.setCharacterSize(14);
	textCost.setCharacterSize(14);
}

int Weapon::getFill() {
	return fill;
}

int Weapon::getDamage() {
	return damage;
}

int Weapon::getRange() {
	return range;
}

int Weapon::getCost() {
	return cost;
}

void Weapon::drawWeaponSprite(sf::RenderWindow& window, int i, std::ostringstream& string) {
	string << this->getDamage();
	textDamage.setString(string.str());
	string.str("");

	string << this->getRange();
	textRange.setString(string.str());
	string.str("");

	string << this->getCost();
	textCost.setString(string.str());
	string.str("");

	switch (i) {
	case 0:
		weaponSprite.setPosition(22 * 32 + 5, 5  * 32 - 5);
		textDamage.setPosition(20.5 * 32 + 1, 6 * 32 );
		textRange.setPosition(22.5 * 32 + 3, 6 * 32 );
		textCost.setPosition(24.5 * 32 - 2, 6 * 32 );
		break;

	case 1:
		weaponSprite.setPosition(22 * 32 + 5, 7 * 32 - 5);
		textDamage.setPosition(20.5 * 32 + 1, 8 * 32);
		textRange.setPosition(22.5 * 32 + 3, 8 * 32);
		textCost.setPosition(24.5 * 32 - 2, 8 * 32);
		break;

	case 2:
		weaponSprite.setPosition(22 * 32 + 5, 9 * 32 - 5);
		textDamage.setPosition(20.5 * 32 + 1, 10 * 32);
		textRange.setPosition(22.5 * 32 + 3, 10 * 32);
		textCost.setPosition(24.5 * 32 - 2, 10 * 32);
		break;
	}
	window.draw(weaponSprite);
	window.draw(textDamage);
	window.draw(textRange);
	window.draw(textCost);
}

sf::Sprite& Weapon::getWeaponSprite() {
	return weaponSprite;
}

//Hammer

Hammer::Hammer() {
	this->setDamage(20);
	this->setRange(1);
	this->setCost(3);
}

Hammer::Hammer(Textures& textures) {
	this->setFill();
	this->setDamage(20);
	this->setRange(1);
	this->setCost(3);
	this->setWeaponSprite(0, 1, textures);
}

//Rifle

Rifle::Rifle() {
	this->setDamage(10);
	this->setRange(5);
	this->setCost(5);
}

Rifle::Rifle(Textures& textures) {
	this->setFill();
	this->setDamage(10);
	this->setRange(5);
	this->setCost(5);
	this->setWeaponSprite(0, 0, textures);
}