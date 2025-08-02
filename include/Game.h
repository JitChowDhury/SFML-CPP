#pragma once 

#include<SFML\Graphics.hpp>

class Game
{
private:
	sf::RenderWindow window;
	sf::Clock clock;
	float deltaTime;


	void HandleEvents();
	void Update();
	void Render();
public:
	Game();
	void run();
};