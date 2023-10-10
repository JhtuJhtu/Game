#pragma once
#include <SFML/Graphics.hpp>

class Textures
{
public:
	Textures();
	sf::Texture& getTileTexture();
	sf::Texture& getActorTexture();
	sf::Texture& getWeaponTexture();
	sf::Font& getFont();
private:
	sf::Texture tileTexture;
	sf::Texture actorTexture;
	sf::Texture weaponTexture;
	sf::Font font;
};

