#include "Player.h"

Player::Player(const std::string& textureFile, sf::Vector2f position, float speed) :
	speed(speed),
	isRed(true),
	health(100.f),
	animation(0.05f)
{
	if (!texture.loadFromFile(textureFile))
	{
		texture.create(32, 32);
		sf::Image image;
		image.create(32, 32, sf::Color::Red);
		texture.loadFromImage(image);
	}

	sprite.setTexture(texture);
	sprite.setPosition(position);
	sprite.setOrigin(16.f, 16.f);
	sprite.setScale(3, 3);

	animation.addFrame(sf::IntRect(0, 0, 32, 32));
	animation.addFrame(sf::IntRect(32, 0, 32, 32));
	animation.addFrame(sf::IntRect(64, 0, 32, 32));
	animation.addFrame(sf::IntRect(96, 0, 32, 32));
	animation.addFrame(sf::IntRect(128, 0, 32, 32));
	animation.addFrame(sf::IntRect(160, 0, 32, 32));

}

void Player::update(float dt, unsigned int windowWidth, unsigned int windowHeight)
{
	animation.update(dt);
	sprite.setTextureRect(animation.getCurrentFrame());

	sf::Vector2f movement(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		movement.y -= speed * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		movement.y += speed * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		movement.x -= speed * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		movement.x += speed * dt;
	}
	sprite.move(movement);

	sf::Vector2f pos = sprite.getPosition();
	sf::FloatRect bounds = sprite.getGlobalBounds();

	if (pos.x - bounds.width / 2 < 0.f)pos.x = bounds.width / 2;
	if (pos.x + bounds.width / 2 > windowWidth)pos.x = windowWidth - bounds.width / 2;
	if (pos.y - bounds.height / 2 < 0.f)pos.y = bounds.height / 2;
	if (pos.y + bounds.height / 2 > windowHeight)pos.y = windowHeight -bounds.height / 2;
	sprite.setPosition(pos);

}

void Player::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

sf::FloatRect Player::getBounds() const
{
	return sprite.getGlobalBounds();
}

float Player::getRadius() const
{
	return sprite.getGlobalBounds().width / 2.f;
}

void Player::handleInput(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
		isRed = !isRed;
		sf::Image image;
		image.create(32, 32, isRed ? sf::Color::Red : sf::Color::Blue);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
}

float Player::getHealth() const
{
	return health;
}

void Player::takeDamage(float damage)
{
	health = std::max(0.f, health - damage);
}

sf::Vector2f Player::getPosition() const {
	return sprite.getPosition();
}
