#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameObject.h"
#include "Animation.h"

class Player :public GameObject
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	Animation animation;
	float speed; //pixels per second
	bool isRed;
	float health;

	sf::SoundBuffer hitBuffer;
	sf::Sound hitSound;

public:
	Player(const std::string& textureFile, sf::Vector2f position, float speed);
	void update(float dt, unsigned int windowWidth, unsigned int windowHeight) override;
	void draw(sf::RenderWindow& window) const override;
	sf::FloatRect getBounds() const override;
	float getRadius() const override; // New
	void handleInput(const sf::Event& event) override;
	float getHealth() const override;
	void takeDamage(float damage) override;
	sf::Vector2f getPosition() const;
};