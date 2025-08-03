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

void Ball::Update(float deltaTime, unsigned int windowWidth, unsigned int windowHeight)
{
	shape.move(velocity * deltaTime);

	sf::Vector2f pos = shape.getPosition();
	float radius = shape.getRadius();

	if (pos.x - radius <= 0.f || pos.x + radius >= windowWidth)
	{
		velocity.x = -velocity.x;
		if (pos.x - radius <= 0.f) pos.x = radius;
		else pos.x = windowWidth - radius;

		shape.setPosition(pos);
	}

	if (pos.y - radius <= 0.f || pos.y + radius >= windowHeight) {
		velocity.y = -velocity.y; 
		if (pos.y - radius <= 0.f) pos.y = radius;
		else pos.y = windowHeight - radius;
		shape.setPosition(pos);
	}
}

void Ball::Draw(sf::RenderWindow& window) const
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
