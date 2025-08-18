#include "SlowEnemy.h"

SlowEnemy::SlowEnemy(const std::string& textureFile, sf::Vector2f position, float speed)
    : Enemy(textureFile, position, speed * 0.5f) { // 0.5x speed
    health = 200.f; // High health
}

void SlowEnemy::update(float dt, unsigned int windowWidth, unsigned int windowHeight, const sf::Vector2f& playerPos) {
    Enemy::update(dt, windowWidth, windowHeight, playerPos);
}