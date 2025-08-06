#include "Animation.h"

Animation::Animation(float frameTime):frameTime(frameTime),currentTime(0.f),currentFrame(0)
{
}

void Animation::addFrame(const sf::IntRect& frame)
{
	frames.push_back(frame);
}

void Animation::update(float dt)
{
	currentTime += dt;
	if (currentTime>=frameTime)
	{
		currentTime -= frameTime;
		currentFrame = (currentFrame + 1) % frames.size();
	}
}
const sf::IntRect& Animation::getCurrentFrame() const {
	return frames[currentFrame];
}