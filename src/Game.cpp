#include "Game.h"
#include <iostream>
#include <sstream>

Game::Game():window(sf::VideoMode(1024,768),"SFML GAME"),deltaTime{0.f},
player("assets/player.png", sf::Vector2f(400.f, 500.f), 200.f),score(0)
{
	window.setFramerateLimit(120);
	balls.emplace_back(25.f, sf::Vector2f(400.f, 300.f), sf::Color::Green, sf::Vector2f(400.f, 150.f));
	balls.emplace_back(30.f, sf::Vector2f(900.f, 150.f), sf::Color::White, sf::Vector2f(1000.f, 750.f));
	
	if (!font.loadFromFile("assets/arial.ttf"))
	{

	}
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(10.f, 10.f);
	scoreText.setString("Score: 0");

	fpsText.setFont(font);
	fpsText.setCharacterSize(24);
	fpsText.setFillColor(sf::Color::Green);
	fpsText.setPosition(140.f, 10.f);
	fpsText.setString("FPS: 0");
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
	deltaTime = deltaClock.restart().asSeconds();//returns the time took to render last frame as seconds
	player.Update(deltaTime, window.getSize().x, window.getSize().y);
	for (auto it = balls.begin(); it != balls.end();)
	{
		it->Update(deltaTime, window.getSize().x, window.getSize().y);
		if (player.getBounds().intersects(it->getBounds()))
		{
			score++;
			it = balls.erase(it);
		}
		else
		{
			++it;
		}

		std::stringstream ss;
		ss << "Score: " << score;
		scoreText.setString(ss.str());
	}



	sf::Time elapsed = elapsedClock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		std::stringstream fpss;
		fpss << "FPS: " << (int) (1 / deltaTime);
		fpsText.setString(fpss.str());
	    elapsedClock.restart();

	}

}

void Game::Render()
{
	window.clear();
	player.Draw(window);
	for (const auto& ball : balls) {
		ball.Draw(window);
	}
	window.draw(scoreText);
	window.draw(fpsText);
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
