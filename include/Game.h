#pragma once 
#include<vector>
#include<SFML\Graphics.hpp>
#include"GameObject.h"
#include "Ball.h"
#include "Player.h"
#include "Enemy.h"
#include "FastEnemy.h"
#include "SlowEnemy.h"
#include "PowerUp.h"
#include "ParticleSystem.h"

enum class GameState {PLAY, PAUSE , GAME_OVER,START};

class Game
{
private:
	sf::RenderWindow window;
	sf::Clock deltaClock;   
	sf::Clock elapsedClock;
	GameState state;
	float deltaTime;
	float ballSpawnTimer;
	float ballSpawnInterval;
	std::vector<std::unique_ptr<GameObject>> objects;
	Player* player;
	sf::Font font;
	sf::Text scoreText;
	sf::Text fpsText;
	sf::Text stateText;
	sf::RectangleShape healthBar;
	int score;


	int level;
	float levelTimer,multiplier, multiplierTimer;
	float powerUpSpawnTimer, powerUpSpawnInterval;

	sf::Text startText;
	sf::Text pauseText;
	sf::Text restartText;


	sf::SoundBuffer collectBuffer;
	sf::Sound collectSound;
	ParticleSystem particleSystem;
	




	void HandleEvents();
	void Update();
	void Render();
public:
	Game();
	void run();
};