#pragma once
#include<SFML\Graphics.hpp>

class Ball
{
private:
	sf::CircleShape shape;
	sf::Vector2f velocity;
public:
	Ball(float radius, sf::Vector2f position, sf::Color color, sf::Vector2f velocity);
	void Update(float deltaTime, int windowWidth, int WindowHeight);
	void Draw(sf::RenderWindow& draw) const;
	sf::Vector2f getPosition() const;

};