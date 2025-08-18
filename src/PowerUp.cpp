#include "PowerUp.h"

PowerUp::PowerUp(const std::string& textureFile, sf::Vector2f position) // : animation(0.1f)  // Optional initializer
{
    if (!texture.loadFromFile(textureFile)) {
        texture.create(32, 32);
        sf::Image image;
        image.create(32, 32, sf::Color::Cyan);
        texture.loadFromImage(image);
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setOrigin(16.f, 16.f);
    // animation.addFrame(sf::IntRect(0, 0, 32, 32));  // Optional: If animation needed
}

void PowerUp::update(float dt, unsigned int windowWidth, unsigned int windowHeight, const sf::Vector2f& playerPos) {
    // Stationary, no update needed
    // animation.update(dt);  // Optional
    // sprite.setTextureRect(animation.getCurrentFrame());  // Optional
}

void PowerUp::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect PowerUp::getBounds() const {
    return sprite.getGlobalBounds();
}

float PowerUp::getRadius() const {
    return sprite.getGlobalBounds().width / 2.f;
}

void PowerUp::handleInput(const sf::Event& event) {
    // No input handling
}

float PowerUp::getHealth() const {
    return 0.f;
}

void PowerUp::takeDamage(float damage) {
    // No damage handling
}