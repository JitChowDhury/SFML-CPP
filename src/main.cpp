#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <ctime>

int main() {
    // Initialize window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Endless Runner");
    window.setFramerateLimit(60);

    // Player properties
    sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
    player.setFillColor(sf::Color::Green);
    player.setPosition(100.f, 500.f);
    float playerVelocityY = 0.f;
    const float gravity = 0.5f;
    const float jumpStrength = -15.f;
    bool isJumping = false;

    // Ground properties
    sf::RectangleShape ground(sf::Vector2f(800.f, 100.f));
    ground.setFillColor(sf::Color::Yellow);
    ground.setPosition(0.f, 500.f);

    // Obstacle properties
    std::vector<sf::RectangleShape> obstacles;
    float obstacleSpawnTimer = 0.f;
    const float obstacleSpawnInterval = 100.f;
    std::mt19937 rng(static_cast<unsigned>(time(nullptr)));
    std::uniform_real_distribution<float> dist(50.f, 150.f);

    // Game variables
    float scrollSpeed = -5.f;
    bool gameOver = false;

    // Game loop
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space && !isJumping && !gameOver) {
                    playerVelocityY = jumpStrength;
                    isJumping = true;
                }
                if (event.key.code == sf::Keyboard::R && gameOver) {
                    // Reset game
                    obstacles.clear();
                    player.setPosition(100.f, 500.f);
                    playerVelocityY = 0.f;
                    isJumping = false;
                    gameOver = false;
                    scrollSpeed = -5.f;
                }
            }
        }

        if (!gameOver) {
            // Update player
            playerVelocityY += gravity;
            player.move(0.f, playerVelocityY);
            if (player.getPosition().y >= 500.f) {
                player.setPosition(player.getPosition().x, 500.f);
                playerVelocityY = 0.f;
                isJumping = false;
            }

            // Spawn obstacles
            obstacleSpawnTimer += 1.f;
            if (obstacleSpawnTimer >= obstacleSpawnInterval) {
                sf::RectangleShape obstacle(sf::Vector2f(30.f, 50.f));
                obstacle.setFillColor(sf::Color::Red);
                obstacle.setPosition(800.f, 500.f);
                obstacles.push_back(obstacle);
                obstacleSpawnTimer = dist(rng);
            }

            // Update obstacles
            for (auto it = obstacles.begin(); it != obstacles.end();) {
                it->move(scrollSpeed, 0.f);
                if (it->getPosition().x < -30.f) {
                    it = obstacles.erase(it);
                }
                else {
                    // Collision detection
                    if (player.getGlobalBounds().intersects(it->getGlobalBounds())) {
                        gameOver = true;
                        scrollSpeed = 0.f;
                    }
                    ++it;
                }
            }
        }

        // Render
        window.clear(sf::Color::Cyan);
        window.draw(ground);
        for (const auto& obstacle : obstacles) {
            window.draw(obstacle);
        }
        window.draw(player);
        window.display();
    }

    return 0;
}