#pragma once
#include "Engine.h"

#include <Windows.h>
int main()
{
	ShowWindow(::GetConsoleWindow(), SW_HIDE);
	int windowHeight = 820;
	int windowWidth = 480;
	sf::RenderWindow window (sf::VideoMode(windowHeight, windowWidth), "", sf::Style::Close);
	window.setFramerateLimit(60);

	Engine engine;
	engine.startGame(window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			engine.update(window, event);
		}
		
	}
	
	return 0;
}