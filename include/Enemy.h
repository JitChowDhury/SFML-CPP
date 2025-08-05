#pragma once
#include <SFML\Graphics.hpp>
#include "GameObject.h"

class Enemy :public GameObject
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f velocity;
public:
	Enemy(const std::string& textureFile, sf::Vector2f position, sf::Vector2f velocity);
	void update(float dt, unsigned int windowWidth, unsigned int windowHeight) override;
	void draw(sf::RenderWindow& window) const override;
	sf::FloatRect getBounds() const override;
	float getRadius() const override;
	void handleInput(const sf::Event& event) override;


};
