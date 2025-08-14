#include "Player.h"

//constructor initialization list
Player::Player(const std::string& textureFile, sf::Vector2f position, float speed) :
	speed(speed),
	isRed(true),
	health(100.f),
	animation(0.05f)
{
	//load from texturefile
	if (!texture.loadFromFile(textureFile))
	{
		texture.create(32, 32);

		//fallback image
		sf::Image image;
		image.create(32, 32, sf::Color::Red);
		texture.loadFromImage(image);
	}

	sprite.setTexture(texture);
	sprite.setPosition(position);
	sprite.setOrigin(16.f, 16.f);
	sprite.setScale(3, 3);
	//pushpack all sprites from the spritesheet
	animation.addFrame(sf::IntRect(0, 0, 32, 32));
	animation.addFrame(sf::IntRect(32, 0, 32, 32));
	animation.addFrame(sf::IntRect(64, 0, 32, 32));
	animation.addFrame(sf::IntRect(96, 0, 32, 32));
	animation.addFrame(sf::IntRect(128, 0, 32, 32));
	animation.addFrame(sf::IntRect(160, 0, 32, 32));
	//add sound
	if (!hitBuffer.loadFromFile("assets/hit.wav"))
	{

	}
	hitSound.setBuffer(hitBuffer);

}


void Player::update(float dt, unsigned int windowWidth, unsigned int windowHeight)
{
	//update animation (set next frame in vector if time has passed)
	animation.update(dt);
	
	sprite.setTextureRect(animation.getCurrentFrame());//set the texture 


	//player movement
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

	//based on movement sprite faces
	movement.x > 0 ? sprite.setScale(3, 3) : sprite.setScale(-3, 3);
	sprite.move(movement);

	//get position and bounds
	sf::Vector2f pos = sprite.getPosition();
	sf::FloatRect bounds = sprite.getGlobalBounds();

	//if left
	if (pos.x - bounds.width / 2 < 0.f)pos.x = bounds.width / 2;
	//right
	if (pos.x + bounds.width / 2 > windowWidth)pos.x = windowWidth - bounds.width / 2;
	//top
	if (pos.y - bounds.height / 2 < 0.f)pos.y = bounds.height / 2;

	//bottom
	if (pos.y + bounds.height / 2 > windowHeight)pos.y = windowHeight -bounds.height / 2;
	//set the sprite position
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
	//take damage on enemy hit
	health = std::max(0.f, health - damage);
	if (damage > 0.f)hitSound.play();//play sound on damage
}

sf::Vector2f Player::getPosition() const {
	return sprite.getPosition();
}
