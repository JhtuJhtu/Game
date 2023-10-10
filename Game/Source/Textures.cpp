#include "Textures.h"

Textures::Textures() {
	tileTexture.loadFromFile("images/tile.png");
	actorTexture.loadFromFile("images/actor.png");
	weaponTexture.loadFromFile("images/weapon.png");
	font.loadFromFile("images/font.otf");
}

sf::Texture& Textures::getTileTexture() {
	return tileTexture;
}

sf::Texture& Textures::getActorTexture() {
	return actorTexture;
}

sf::Texture& Textures::getWeaponTexture() {
	return weaponTexture;
}

sf::Font& Textures::getFont() {
	return font;
}