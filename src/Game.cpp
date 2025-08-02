#include "Game.h"

Game::Game():window(sf::VideoMode(940,560),"SFML GAME"),deltaTime{0.f}
{
	
}

void Game::HandleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			window.close();
		}
	}
}

void Game::Update()
{
	deltaTime = clock.restart().asSeconds();
}

void Game::Render()
{
	window.clear();
	//draw
	window.display();
}




void Game::run()
{
	while (window.isOpen())
	{
		HandleEvents();
		Update();
		Render();
	}
}
