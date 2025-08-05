#include "Enemy.h"

Enemy::Enemy(const std::string& textureFile, sf::Vector2f position, sf::Vector2f velocity):velocity(velocity)
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
}

void Enemy::update(float dt, unsigned int windowWidth, unsigned int windowHeight)
{
	sprite.move(velocity * dt);
	sf::Vector2f pos = sprite.getPosition();
	sf::FloatRect bounds = sprite.getGlobalBounds();

	if (pos.x - bounds.width / 2 <= 0.f || pos.x + bounds.width / 2 >= windowWidth)
	{
		velocity.x = -velocity.x;
		if (pos.x - bounds.width / 2 <= 0.f) pos.x = bounds.width / 2;
		else pos.x = windowWidth - bounds.width / 2;
		sprite.setPosition(pos);

	}
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
