#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Animation.h"

class FastEnemy :public Enemy
{
public:
	FastEnemy(const std::string& textureFile, sf::Vector2f position, float speed);
	void update(float deltaTime,unsigned int windowWidth , unsigned int windowHeight , const sf::Vector2f& playerPos) override;
};
