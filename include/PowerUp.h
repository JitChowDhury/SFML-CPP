#pragma once
#include <SFML/Graphics.hpp>  // Fixed include
#include "GameObject.h"
// #include "Animation.h"  // Optional: Comment out if no animation needed

class PowerUp : public GameObject {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    // Animation animation;  // Optional: If adding animation

public:
    PowerUp(const std::string& textureFile, sf::Vector2f position);
    void update(float dt, unsigned int windowWidth, unsigned int windowHeight, const sf::Vector2f& playerPos) override;
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;
    float getRadius() const override;
    void handleInput(const sf::Event& event) override;
    float getHealth() const override;
    void takeDamage(float damage) override;
};