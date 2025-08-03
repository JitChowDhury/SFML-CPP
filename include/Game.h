#pragma once 
#include<vector>
#include<SFML\Graphics.hpp>
#include "Ball.h"
#include "Player.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Clock deltaClock;   
	sf::Clock elapsedClock;
	float deltaTime;
	Player player;
	std::vector<Ball> balls;
	sf::Font font;
	sf::Text scoreText;
	int score;



	void HandleEvents();
	void Update();
	void Render();
public:
	Game();
	void run();
};