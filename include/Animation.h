#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

class Animation
{
private:
	std::vector<sf::IntRect> frames;
	float frameTime;
	float currentTime;
	size_t currentFrame;

public:
	Animation(float frameTime);
	void addFrame(const sf::IntRect& frame);
	void update(float deltaTime);
	consf sf::IntRect& getCurrentFrame() const;
};