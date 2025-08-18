#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Animation.h"

class RangedEnemy : public Enemy {
private:
    float attackTimer, attackInterval;

public:
    RangedEnemy(const std::string& textureFile, sf::Vector2f position, float speed);
    void update(float dt, unsigned int windowWidth, unsigned int windowHeight, const sf::Vector2f& playerPos) override;
};