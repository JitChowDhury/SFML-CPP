#pragma once
#include<SFML\Graphics.hpp>
#include "GameObject.h"

class Ball:public GameObject
{
private:
	sf::CircleShape shape;
	sf::Vector2f velocity;
public:
	Ball(float radius, sf::Vector2f position, sf::Color color, sf::Vector2f velocity);
	void Update(float deltaTime,unsigned int windowWidth, unsigned int WindowHeight) override;
	void Draw(sf::RenderWindow& draw) const override;
	sf::Vector2f getPosition() const;

	sf::FloatRect getBounds() const override;


};