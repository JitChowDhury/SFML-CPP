#pragma once
#include <SFML/Graphics.hpp>
//abstract class
class GameObject
{
public:
	virtual ~GameObject() = default;
	//update (deltatime , windowWidth , windowHeight);
	virtual void update(float dt, unsigned int windowWidth, unsigned int windowHeight) = 0;
	//draw in renderWindow(pass by ref cause window is large object)
	virtual void draw(sf::RenderWindow& window) const = 0;
	//return the bounds
	virtual sf::FloatRect getBounds() const = 0;
	//getradius
	virtual float getRadius() const = 0;
	//handleInput
	virtual void handleInput(const sf::Event& event) = 0;
	//return the health
	virtual float getHealth()const = 0;
	
	virtual void takeDamage(float damage) = 0;

};