#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Player :public GameObject
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float speed; //pixels per second
	bool isRed;

public:
	Player(const std::string& textureFile, sf::Vector2f position, float speed);
	void update(float dt, unsigned int windowWidth, unsigned int windowHeight) override;
	void draw(sf::RenderWindow& window) const override;
	sf::FloatRect getBounds() const override;
	float getRadius() const override; // New
	void handleInput(const sf::Event& event) override;
};