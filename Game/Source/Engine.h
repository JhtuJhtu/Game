#pragma once
#include <memory>

#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "Floor.h"
#include "Actor.h"
#include "Gui.h"

class Engine {
public:
	Engine();
	void startGame(sf::RenderWindow& window);
	void update(sf::RenderWindow& window, sf::Event event);
private:
	Textures textures;
	std::shared_ptr<Floor> nFloor;
	std::shared_ptr<Player> player;
	Gui gui;
	Target target;
	int currentRoomY;
	int currentRoomX;
	int floorNumber;
};