#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

class Animation
{
private:
	// Vector to store the sequence of frames, each represented as an sf::IntRect (a rectangle defining a portion of a sprite sheet)
	std::vector<sf::IntRect> frames;
	// Duration (in seconds) that each frame should be displayed
	float frameTime;
	// Accumulated time since the last frame change, used to track when to switch frames
	float currentTime;
	// Index of the currently active frame in the frames vector
	size_t currentFrame;

public:
	// Constructor: Initializes the animation with a specified frame duration
	// @param frameTime: Time (in seconds) each frame is displayed
	Animation(float frameTime);
	// Adds a new frame to the animation sequence
	// @param frame: An sf::IntRect defining the position and size of the frame on a sprite sheet
	void addFrame(const sf::IntRect& frame);
	// Updates the animation state based on elapsed time
   // @param deltaTime: Time elapsed since the last update (in seconds)
	void update(float deltaTime);
	// Retrieves the current frame's rectangle for rendering
   // @return: Reference to the current frame's sf::IntRect
   // Marked const to ensure it doesn't modify the Animation object
	const sf::IntRect& getCurrentFrame() const;
};