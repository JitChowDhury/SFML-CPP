#include "Game.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <filesystem>
#include <random>



Game::Game() :window(sf::VideoMode(1024, 768), "SFML GAME"),
deltaTime{ 0.f },
score(0),
particleSystem(sf::Color::Blue, 2.f, 0.5f),
state(GameState::START),
ballSpawnInterval(2.0f),
ballSpawnTimer(0.f),
level(1),
levelTimer(0.f),
multiplier(1.f),
multiplierTimer(0.f)
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

	startText.setFont(font);
	startText.setCharacterSize(32);
	startText.setString("Click to Start"); 
	startText.setPosition(300.f, 300.f); 
	pauseText.setFont(font);
	pauseText.setCharacterSize(32);
	pauseText.setFillColor(sf::Color::White);
	pauseText.setString("Resume"); 
	pauseText.setPosition(300.f, 300.f); 
	restartText.setFont(font);
	restartText.setCharacterSize(32);
	restartText.setString("Restart");
	restartText.setPosition(300.f, 300.f);
	restartText.setFillColor(sf::Color::Red);


	healthBar.setSize(sf::Vector2f(100.f, 10.f));
	healthBar.setFillColor(sf::Color::Green);
	healthBar.setPosition(10.f, 40.f);

	if (!collectBuffer.loadFromFile("assets/collect.wav")) {}
	collectSound.setBuffer(collectBuffer);

	

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

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
			if (state == GameState::START && startText.getGlobalBounds().contains(mousePos))
			{
				state = GameState::PLAY;
			}

			if (state == GameState::PAUSE && pauseText.getGlobalBounds().contains(mousePos))
			{
				state = GameState::PLAY;
			}
			if (restartText.getGlobalBounds().contains(mousePos) && state == GameState::GAME_OVER)
			{
				score = 0;
				level = 1;
				multiplier = 1.f;
				state = GameState::PLAY;
				objects.clear();
				particleSystem.clearParticle();
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
	

	levelTimer += deltaTime; // New
	if (levelTimer >= 30.f) { // New
		level++;
		levelTimer = 0.f;
		objects.emplace_back(std::make_unique<Enemy>("assets/enemy.png", sf::Vector2f(100.f, 100.f), 100.f + level * 20.f));
		objects.emplace_back(std::make_unique<Ball>(20.f, sf::Vector2f(600.f, 100.f), sf::Color::Yellow, sf::Vector2f(-150.f - level * 50.f, 100.f)));

	}

	multiplierTimer -= deltaTime; // New
	if (multiplierTimer <= 0.f) multiplier = 1.f; // New

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
				score += static_cast<int>(1 * multiplier); // Updated with multiplier
				multiplier += 0.5f; // New
				multiplierTimer = 3.f; // New
				collectSound.play();

				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_real_distribution<float> dist(-100.f, 100.f);
				for (int i = 0; i < 10; ++i) {
					particleSystem.addParticle(ballPos, sf::Vector2f(dist(gen), dist(gen)));
				}
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
	if (state == GameState::START) { // New
		window.draw(startText);
	}
	else if (state == GameState::PAUSE) { // New
		for (const auto& obj : objects) {
			obj->draw(window);
		}
		particleSystem.draw(window);
		window.draw(scoreText);
		window.draw(healthBar);
		window.draw(pauseText);
	}
	else if (state == GameState::GAME_OVER)
	{
		window.draw(restartText);
	}
	else {
		for (const auto& obj : objects) {
			obj->draw(window);
		}
		particleSystem.draw(window);
		window.draw(scoreText);
		window.draw(healthBar);
		window.draw(stateText);
	}
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
