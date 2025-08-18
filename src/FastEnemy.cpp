#include "FastEnemy.h"

FastEnemy::FastEnemy(const std::string& textureFile, sf::Vector2f position, float speed)
    : Enemy(textureFile, position, speed * 1.5f) { // 1.5x speed
    health = 50.f; // Low health
}

void FastEnemy::update(float dt, unsigned int windowWidth, unsigned int windowHeight, const sf::Vector2f& playerPos) {
    Enemy::update(dt, windowWidth, windowHeight, playerPos); // Reuse base
}