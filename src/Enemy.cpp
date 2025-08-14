#include "Enemy.h"
#include<cmath>
#include<iostream>

Enemy::Enemy(const std::string& textureFile, sf::Vector2f position, float speed) :
	speed(speed),
	health(100.f),
	animation(0.1f)
{
	if (!texture.loadFromFile(textureFile))
	{
		texture.create(32, 32);
		sf::Image image;
		image.create(32, 32, sf::Color::Magenta);
		texture.loadFromImage(image);
	}
	sprite.setTexture(texture);
	sprite.setPosition(position);
	sprite.setOrigin(16.f, 16.f);
	sprite.setScale(2, 2);
	
	animation.addFrame(sf::IntRect(0, 0, 32, 32));
	animation.addFrame(sf::IntRect(32, 0, 32, 32));
	animation.addFrame(sf::IntRect(64, 0, 32, 32));
	animation.addFrame(sf::IntRect(96, 0, 32, 32));
	animation.addFrame(sf::IntRect(128, 0, 32, 32));
	animation.addFrame(sf::IntRect(160, 0, 32, 32));
}

void Enemy::update(float dt, unsigned int windowWidth, unsigned int windowHeight)
{
	

	animation.update(dt);
	sprite.setTextureRect(animation.getCurrentFrame());

	//direction to player
	sf::Vector2f direction = playerPos - sprite.getPosition();

	direction.x > 0 ? sprite.setScale(1, 1) : sprite.setScale(-1, 1);//face based on direction
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);//length
	if (length > 0.f) {
		direction /= length; // Normalize
		sprite.move(direction * speed * dt);

		//if (pos.x - bounds.width / 2 <= 0.f || pos.x + bounds.width / 2 >= windowWidth)
		//{
		//	velocity.x = -velocity.x;
		//	if (pos.x - bounds.width / 2 <= 0.f) pos.x = bounds.width / 2;
		//	else pos.x = windowWidth - bounds.width / 2;
		//	sprite.setPosition(pos);

		//}
	}
	std::cout << "ENEMY IS UPDATING" << std::endl;
}

void Enemy::update(float dt, unsigned int windowWidth, unsigned int windowHeight, const sf::Vector2f& playerPos)
{
	this->playerPos = playerPos; // Store the player position
}

void Enemy::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

sf::FloatRect Enemy::getBounds() const
{
	return sprite.getGlobalBounds();
}

float Enemy::getRadius() const
{
	return sprite.getGlobalBounds().width/2.f;
}

void Enemy::handleInput(const sf::Event& event)
{

}
float Enemy::getHealth() const {
	return health;
}

void Enemy::takeDamage(float damage) {
	health = std::max(0.f, health - damage);
}
