#include "Game.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <filesystem>



Game::Game():window(sf::VideoMode(1024,768),"SFML GAME"),
deltaTime{0.f},
score(0),
state(GameState::PLAY),
ballSpawnInterval(2.0f),
ballSpawnTimer(0.f)
{
	window.setFramerateLimit(120);
	std::cout << "Working Directory: " << std::filesystem::current_path() << std::endl;
	// Initialize objects
	player = new Player("assets/player.png", sf::Vector2f(400.f, 300.f), 200.f);
	objects.emplace_back(player);
	objects.emplace_back(std::make_unique<PowerUp>("assets/powerup.png", sf::Vector2f(300.f, 300.f)));
	objects.emplace_back(std::make_unique<Ball>(20.f, sf::Vector2f(200.f, 200.f), sf::Color::Green, sf::Vector2f(150.f, 100.f)));
	objects.emplace_back(std::make_unique<Ball>(20.f, sf::Vector2f(600.f, 400.f), sf::Color::Yellow, sf::Vector2f(-200.f, -150.f)));
	objects.emplace_back(std::make_unique<Enemy>("assets/enemy.png", sf::Vector2f(100.f, 100.f), 100.f));

	if (!font.loadFromFile("assets/Planes_ValMore.ttf"))
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

	healthBar.setSize(sf::Vector2f(100.f, 10.f));
	healthBar.setFillColor(sf::Color::Green);
	healthBar.setPosition(10.f, 40.f);




	

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
			if (event.key.code == sf::Keyboard::R && state == GameState::GAME_OVER)
			{
				score = 0;
				state = GameState::PLAY;
				objects.clear();
				player = new Player("assets/player.png", sf::Vector2f(400.f, 300.f), 200.f);
				objects.emplace_back(player);
				objects.emplace_back(std::make_unique<PowerUp>("assets/powerup.png", sf::Vector2f(600.f, 300.f)));
				objects.emplace_back(std::make_unique<Ball>(20.f, sf::Vector2f(200.f, 200.f), sf::Color::Green, sf::Vector2f(150.f, 100.f)));
				objects.emplace_back(std::make_unique<Ball>(20.f, sf::Vector2f(600.f, 400.f), sf::Color::Yellow, sf::Vector2f(-200.f, -150.f)));
				objects.emplace_back(std::make_unique<Enemy>("assets/enemy.png", sf::Vector2f(100.f, 100.f), 100.f));
			}
		}

		if (state == GameState::PLAY )
		{
			for (auto& obj : objects)
			{
				obj->handleInput(event);
            }
		}		

	}
}

void Game::Update()
{
	deltaTime = deltaClock.restart().asSeconds();//returns the time took to render last frame as seconds
	ballSpawnTimer += deltaTime;
	if (ballSpawnTimer >= ballSpawnInterval)
	{
		ballSpawnTimer -= ballSpawnInterval;
		objects.emplace_back(std::make_unique<Ball>(20.f, sf::Vector2f(rand() % window.getSize().x, rand() % window.getSize().y), sf::Color::Green, sf::Vector2f(rand() % 200 - 100, rand() % 200 - 100)));
	}
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


	sf::Vector2f playerPos = player->getPosition();
	for (auto& obj : objects)
	{
		if (Enemy* enemy = dynamic_cast<Enemy*>(obj.get())) {
			enemy->update(deltaTime, window.getSize().x, window.getSize().y, playerPos);
			enemy->update(deltaTime, window.getSize().x, window.getSize().y);
		}
		else {
			obj->update(deltaTime, window.getSize().x, window.getSize().y);
		}
	}

	for (auto it = objects.begin(); it != objects.end();)
	{
		if (Ball* ball = dynamic_cast<Ball*>(it->get()))//if cast succeds then no null and if block executes and if null then skip
		{
			sf::Vector2f playerPos = player->getBounds().getPosition() + player->getBounds().getSize() / 2.f;
			sf::Vector2f ballPos = ball->getBounds().getPosition() + ball->getBounds().getSize() / 2.f;

			float distance = std::sqrt(std::pow(ballPos.x - playerPos.x, 2) + std::pow(ballPos.y - playerPos.y, 2));
			if (distance < player->getRadius() + ball->getRadius()) {
				score++;
				it = objects.erase(it);
				continue;
			}
		}
		else if (Enemy* enemy = dynamic_cast<Enemy*>(it->get())) {
			sf::Vector2f playerPos = player->getBounds().getPosition() + player->getBounds().getSize() / 2.f;
			sf::Vector2f enemyPos = enemy->getBounds().getPosition() + enemy->getBounds().getSize() / 2.f;
			float distance = std::sqrt(std::pow(enemyPos.x - playerPos.x, 2) + std::pow(enemyPos.y - playerPos.y, 2));
			if (distance < player->getRadius() + enemy->getRadius()) {
				player->takeDamage(1.f);
				if (player->getHealth() <= 0.f) {
					state = GameState::GAME_OVER;
				}
			}
		}
		else if (PowerUp* powerup = dynamic_cast<PowerUp*>(it->get()))
		{
			sf::Vector2f playerPos = player->getBounds().getPosition() + player->getBounds().getSize() / 2.f;
			sf::Vector2f powerUpPos = powerup->getBounds().getPosition() + powerup->getBounds().getSize() / 2.f;

			float distance = std::sqrt(std::pow(powerUpPos.x - playerPos.x, 2) + std::pow(powerUpPos.y - playerPos.y, 2));

			if (distance < player->getRadius() + powerup->getRadius())
			{
				player->takeDamage(-20.f);
				it = objects.erase(it);
				continue;
			}

		}
		++it;
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

	healthBar.setSize(sf::Vector2f(player->getHealth(), 10.f));
	if (player->getHealth() > 50.f) {
		healthBar.setFillColor(sf::Color::Green);
	}
	else if (player->getHealth() > 20.f) {
		healthBar.setFillColor(sf::Color::Yellow);
	}
	else {
		healthBar.setFillColor(sf::Color::Red);
	}

}

void Game::Render()
{
	window.clear(sf::Color::Black);
	for (const auto& obj : objects) {
		obj->draw(window);
	}
	window.draw(scoreText);
	window.draw(fpsText);
	window.draw(stateText);
	window.draw(healthBar);
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
