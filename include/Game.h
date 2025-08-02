#pragma once 

#include<SFML\Graphics.hpp>
#include "Ball.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Clock clock;
	float deltaTime;
	Ball ball;



	void HandleEvents();
	void Update();
	void Render();
public:
	Game();
	void run();
};