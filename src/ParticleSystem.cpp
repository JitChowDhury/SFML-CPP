#include "ParticleSystem.h"
#include <random>

//constructor initialization list
ParticleSystem::ParticleSystem(sf::Color color, float particleSize, float maxLifeTime) :color(color), particleSize(particleSize), maxLifeTime(maxLifeTime)
{

}
//push particle to the vector
void ParticleSystem::addParticle(const sf::Vector2f position, const sf::Vector2f& velocity)
{
	particles.push_back({ position,velocity,maxLifetime });
}


void ParticleSystem::update(float dt)
{
	//loops throug each particle in the vector and its lifetime decreases , if its 0 or less that it's removed and if it more than 0 then change its position
	for (auto it = particles.begin(); it != particles.end())
	{
		it->lifetime -= dt;
		if (it->lifetime <= 0.f)
		{
			it = particles.erase();
		}
		else
		{
			it->position += it->velocity * dt;
			++it;
		}
	}

}

void ParticleSystem::draw(sf::RenderWindow& window) const
{
	sf::CircleShape shape(particleSize);//circle shape of particlesize and given color
	shape.setOrigin(particleSize, particleSize);
	shape.setFillColor(color);
	for (const auto& particle : particles)
	{
		shape.setPosition(particle.position);
		shape.setScale(1.f, particle.lifetime / maxLifetime);
		window.draw(shape);
	}
	

}
