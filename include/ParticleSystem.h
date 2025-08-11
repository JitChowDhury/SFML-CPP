#pragma once
#include<SFML/Graphics.hpp>
#include <vector>

struct Particle//stores particle with pos velocity and lifetime
{
	sf::Vector2f position;
	sf::Vector2f velocity;
	float lifetime;
};

class ParticleSystem
{
private:
	std::vector<Particle> particles;//vector of particles
	sf::Color color;//color
	float particleSize;
	float maxLifetime;
public:

	ParticleSystem(sf::Color color, float particleSize, float maxLifetime);
	void addParticle(const sf::Vector2f position, const sf::Vector2f& velocity);
	void update(float dt);
	void draw(sf::RenderWindow& window) const;
};