#pragma once
#include <SFML\Graphics.hpp>
#include "GameObject.h"
#include "Animation.h"

class Enemy :public GameObject
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f velocity;
	Animation animation;
	sf::Vector2f playerPos;
	float speed;
public:
	float health;
	Enemy(const std::string& textureFile, sf::Vector2f position, float speed);
	void update(float dt, unsigned int windowWidth, unsigned int windowHeight, const sf::Vector2f& playerPos) override;

	void draw(sf::RenderWindow& window) const override;
	sf::FloatRect getBounds() const override;
	float getRadius() const override;
	void handleInput(const sf::Event& event) override;
	float getHealth() const override;
	void takeDamage(float damage) override;


};
