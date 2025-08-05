#include "Game.h"
#include <iostream>
#include <sstream>
#include <cmath>


Game::Game():window(sf::VideoMode(1024,768),"SFML GAME"),
deltaTime{0.f},
player("assets/player.png", sf::Vector2f(400.f, 500.f), 200.f),
score(0),
state(GameState::PLAY)
{
	window.setFramerateLimit(120);

	//initialize balls
	balls.emplace_back(25.f, sf::Vector2f(400.f, 300.f), sf::Color::Green, sf::Vector2f(400.f, 150.f));
	balls.emplace_back(30.f, sf::Vector2f(900.f, 150.f), sf::Color::White, sf::Vector2f(1000.f, 750.f));

	//intialize enemies
	enemies.emplace_back("assets/enemy.png",sf::Vector2f(100.f, 100.f), sf::Vector2f(100.f, 0.f));

	if (!font.loadFromFile("assets/arial.ttf"))
	{
		std::cerr << "Error: Failed to load font assets/arial.ttf" << std::endl;
	}
	// Initialize stateText
	stateText.setFont(font);
	stateText.setCharacterSize(48);
	stateText.setFillColor(sf::Color::White);
	// Center the text
	sf::FloatRect textRect = stateText.getLocalBounds();
	stateText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	stateText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

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
		if (event.type == sf::Event::KeyPressed )
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
			window.close();
			}
			if (event.key.code == sf::Keyboard::P && state != GameState::GAME_OVER)
			{
				state = (state == GameState::PLAY) ? GameState::PAUSE : GameState::PLAY;
			}
		}

		if (state == GameState::PLAY )
		{
			player.handleInput(event);
				for (auto& ball : balls)
				{
					ball.handleInput(event);
				}
			    for (auto& enemy : enemies)
			    {
					enemy.handleInput(event);
			    }
		}		

	}
}

void Game::Update()
{
	deltaTime = deltaClock.restart().asSeconds();//returns the time took to render last frame as seconds

	//update state text
	if (state == GameState::PAUSE) {
		stateText.setString("Paused");
	}
	else if (state == GameState::GAME_OVER) {
		stateText.setString("Game Over");
	}
	else {
		stateText.setString("");
	}
	if (state != GameState::PLAY) return;

	player.update(deltaTime, window.getSize().x, window.getSize().y);
	for (auto& ball : balls)
	{
		ball.update(deltaTime, window.getSize().x, window.getSize().y);
	}

	for (auto& enemy : enemies)
	{
		enemy.update(deltaTime, window.getSize().x, window.getSize().y);
	}
	//circle based collision player vs balls
	sf::Vector2f playerPos = player.getBounds().getPosition() + player.getBounds().getSize() / 2.f;
	float playerRadius = player.getRadius();
	for (auto it = balls.begin(); it != balls.end();)
	{
		sf::Vector2f ballPos = it->getBounds().getPosition() + it->getBounds().getSize() / 2.f;
		float ballRadius = it->getRadius();
		float dx = ballPos.x - playerPos.x;
		float dy = ballPos.y - playerPos.y;
		float distance = std::sqrt(dx * dx + dy * dy);
		if (distance < ballRadius + playerRadius)
		{
			score++;
			it = balls.erase(it);//returns the next location after removing it
		}
		else
		{
			++it;
		}

	}
	for (const auto& enemy : enemies) {
		sf::Vector2f enemyPos = enemy.getBounds().getPosition() + enemy.getBounds().getSize() / 2.f;
		float enemyRadius = enemy.getRadius();
		float dx = enemyPos.x - playerPos.x;
		float dy = enemyPos.y - playerPos.y;
		float distance = std::sqrt(dx * dx + dy * dy);
		if (distance < playerRadius + enemyRadius) {
			state = GameState::GAME_OVER;
		}
	}

    //update score text
	std::stringstream ss;
	ss << "Score: " << score;
	scoreText.setString(ss.str());
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
	window.clear(sf::Color::Black);
	player.draw(window);
	for (const auto& ball : balls) {
		ball.draw(window);
	}
	for (const auto& enemy : enemies) {
		enemy.draw(window);
	}
	window.draw(scoreText);
	window.draw(fpsText);
	window.draw(stateText);
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
