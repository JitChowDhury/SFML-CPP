#include "Game.h"
#include <iostream>

Game::Game():window(sf::VideoMode(1024,768),"SFML GAME"),deltaTime{0.f},
ball1(25.f, sf::Vector2f(400.f, 300.f), sf::Color::Green, sf::Vector2f(400.f, 150.f)),
ball2(30.f, sf::Vector2f(900.f, 150.f), sf::Color::White, sf::Vector2f(1000.f, 750.f))
{
	window.setFramerateLimit(120);
	
	
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
	deltaTime = deltaClock.restart().asSeconds();
	ball1.Update(deltaTime, window.getSize().x, window.getSize().y);
	ball2.Update(deltaTime, window.getSize().x, window.getSize().y);

	sf::Time elapsed = elapsedClock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
	std::cout << "FPS: " << 1 / deltaTime << std::endl;
	elapsedClock.restart();

	}

}

void Game::Render()
{
	window.clear();
	//draw
	ball1.Draw(window);
	ball2.Draw(window);
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
