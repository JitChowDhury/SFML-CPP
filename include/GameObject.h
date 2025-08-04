#pragma once
#include <SFML/Graphics.hpp>
//abstract class
class GameObject
{
public:
	virtual ~GameObject() = default;
	virtual void Update(float dt, unsigned int windowWidth, unsigned int windowHeight) = 0;
	virtual void Draw(sf::RenderWindow& window) const = 0;
	virtual sf::FloatRect getBounds() const = 0;
};