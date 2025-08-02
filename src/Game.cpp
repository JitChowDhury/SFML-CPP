#include "Game.h"
#include <iostream>

Game::Game():window(sf::VideoMode(1024,768),"SFML GAME"),deltaTime{0.f},ball(25.f, sf::Vector2f(400.f, 300.f),sf::Color::Green, sf::Vector2f(400.f, 150.f))
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
	ball.Update(deltaTime, window.getSize().x, window.getSize().y);

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
