#include "Game.h"

Game::Game():window(sf::VideoMode(940,560),"SFML GAME"),deltaTime{0.f},ball(20.f, sf::Vector2f(400.f, 300.f),sf::Color::Magenta, sf::Vector2f(200.f, 150.f))
{
	window.setFramerateLimit(60);
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
	ball.Update(deltaTime, window.getSize().x, window.getSize().y);
}

void Game::Render()
{
	window.clear();
	//draw
	ball.Draw(window);
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
