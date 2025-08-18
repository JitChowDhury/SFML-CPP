#include "Ball.h"

Ball::Ball(float radius, sf::Vector2f position, sf::Color color, sf::Vector2f velocity):velocity(velocity)
{
	shape.setRadius(radius);
	shape.setPosition(position);
	shape.setFillColor(color);
	shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(2.f);

	shape.setOrigin(radius, radius);
	
}

void Ball::update(float deltaTime, unsigned int windowWidth, unsigned int windowHeight, const sf::Vector2f& playerPos)
{
	velocity.y += 500.f * deltaTime;//gravity
	shape.move(velocity * deltaTime);

	sf::Vector2f pos = shape.getPosition();
	float radius = shape.getRadius();

	//bounce back if collide with bounder
	if (pos.x - radius <= 0.f || pos.x + radius >= windowWidth)
	{
		velocity.x = -velocity.x * 0.8f;
		if (pos.x - radius <= 0.f) pos.x = radius;
		else pos.x = windowWidth - radius;

		shape.setPosition(pos);
	}

	if (pos.y - radius <= 0.f || pos.y + radius >= windowHeight) {
		velocity.y = -velocity.y * 0.8f;
		if (pos.y - radius <= 0.f) pos.y = radius;
		else pos.y = windowHeight - radius;
		shape.setPosition(pos);
	}
}

void Ball::draw(sf::RenderWindow& window) const
{
	window.draw(shape);
}

sf::Vector2f Ball::getPosition() const
{
	return shape.getPosition();
}

sf::FloatRect Ball::getBounds() const {
	return shape.getGlobalBounds();
}

float Ball::getRadius() const
{
	return shape.getRadius();
}

void Ball::handleInput(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		//get mouseposstored in event object
		sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
		if (getBounds().contains(mousePos))
		{
			shape.setFillColor(shape.getFillColor() == sf::Color::Green ? sf::Color::Yellow:sf::Color::Green);
		}
	}
}

float Ball::getHealth() const {
	return 0.f;
}

void Ball::takeDamage(float damage) {}
