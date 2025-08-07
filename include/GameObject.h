#pragma once
#include <SFML/Graphics.hpp>
//abstract class
class GameObject
{
public:
	virtual ~GameObject() = default;
	virtual void update(float dt, unsigned int windowWidth, unsigned int windowHeight) = 0;
	virtual void draw(sf::RenderWindow& window) const = 0;
	virtual sf::FloatRect getBounds() const = 0;
	virtual float getRadius() const = 0;
	virtual void handleInput(const sf::Event& event) = 0;
	virtual float getHealth()const = 0;
	virtual void takeDamage(float damage) = 0;

};