#include "RangedEnemy.h"

RangedEnemy::RangedEnemy(const std::string& textureFile, sf::Vector2f position, float speed)
    : Enemy(textureFile, position, speed), attackTimer(0.f), attackInterval(2.f) {
}

void RangedEnemy::update(float dt, unsigned int windowWidth, unsigned int windowHeight, const sf::Vector2f& playerPos) {
    Enemy::update(dt, windowWidth, windowHeight, playerPos);
    attackTimer += dt;
    if (attackTimer >= attackInterval) {
        attackTimer -= attackInterval;
        // Spawn projectile 
    }
}