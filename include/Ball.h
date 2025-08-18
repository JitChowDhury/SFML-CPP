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
	void update(float deltaTime,unsigned int windowWidth, unsigned int WindowHeight, const sf::Vector2f& playerPos) override;
	void draw(sf::RenderWindow& draw) const override;
	sf::Vector2f getPosition() const;

	sf::FloatRect getBounds() const override;
	float getRadius() const override;
	void handleInput(const sf::Event& event)override;
	float getHealth() const override;
	void takeDamage(float damage) override;


			

};