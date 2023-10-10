#include "Gui.h"

Gui::Gui(Textures& textures) {
	textHp.setFont(textures.getFont());
	textHp.setPosition(20.5 * 32, 1 * 32);
	textHp.setCharacterSize(18);

	textMovePoint.setFont(textures.getFont());
	textMovePoint.setPosition(20.5 * 32, 2 * 32);
	textMovePoint.setCharacterSize(18);

	textWeapon.setFont(textures.getFont());
	textWeapon.setPosition(22 * 32, 3 * 32);
	textWeapon.setCharacterSize(18);
	textWeapon.setString("Weapon");

	textStats.setFont(textures.getFont());
	textStats.setPosition(20 * 32 + 5, 4 * 32);
	textStats.setCharacterSize(14);
	textStats.setString("Damage   Range    Cost");
}



void Gui::drawGui(sf::RenderWindow& window, std::shared_ptr<Player> player) {
	string << player->getHp();
	textHp.setString("Health: " + string.str());
	string.str("");
	string << player->getCurMovePoint() << "/" << player->getMaxMovePoint();
	textMovePoint.setString("Move point: " + string.str());
	string.str("");

	window.draw(textHp);
	window.draw(textMovePoint);
	window.draw(textWeapon);
	window.draw(textStats);

	for (int i = 0; i < 3; i++) {
		if (player->getInventory(i).getFill()) {
			player->getInventory(i).drawWeaponSprite(window, i, string);

		}
	}
}

Target::Target() : targetX(0), targetY(0), targetRange(0) {
	targetTexture.loadFromFile("images/tile.png");

	targetSprite.setTexture(targetTexture);
	targetSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

void Target::setTargetXY(int x, int y) {
	targetX = x;
	targetY = y;
}

void Target::setTargetX(int x) {
	targetX = x;
}

void Target::setTargetY(int y) {
	targetY = y;
}

void Target::setTargetRange(int range) {
	targetRange = range;
}

int Target::getTargetX() {
	return targetX;
}

int Target::getTargetY() {
	return targetY;
}

int Target::getTargetRange() {
	return targetRange;
}

sf::Sprite& Target::getTargetSprite() {
	return targetSprite;
}

void Target::drawTarget(sf::RenderWindow& window) {
	targetSprite.setPosition(targetX * 32, targetY * 32);
	window.draw(targetSprite);
}