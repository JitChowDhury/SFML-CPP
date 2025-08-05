#pragma once 
#include<vector>
#include<SFML\Graphics.hpp>
#include"GameObject.h"
#include "Ball.h"
#include "Player.h"
#include "Enemy.h"

enum class GameState {PLAY, PAUSE , GAME_OVER};

class Game
{
private:
	sf::RenderWindow window;
	sf::Clock deltaClock;   
	sf::Clock elapsedClock;
	GameState state;
	float deltaTime;
	Player player;
	std::vector<Ball> balls;
	std::vector<Enemy> enemies;
	sf::Font font;
	sf::Text scoreText;
	sf::Text fpsText;
	sf::Text stateText;
	int score;




	void HandleEvents();
	void Update();
	void Render();
public:
	Game();
	void run();
};