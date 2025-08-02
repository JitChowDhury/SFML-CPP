#pragma once 

#include<SFML\Graphics.hpp>
#include "Ball.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Clock deltaClock;   
	sf::Clock elapsedClock;
	float deltaTime;
	Ball ball1;
	Ball ball2;



	void HandleEvents();
	void Update();
	void Render();
public:
	Game();
	void run();
};