#include<iostream>
#include<SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(960, 540), "SFML WINDOW");
	//window.setFramerateLimit(60);

	sf::Clock clock;

	sf::CircleShape shape(50.f);
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(200.f, 200.f);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(3.f);
	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		std::cout << "FPS: " << 1 / deltaTime << std::endl;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				std::cout << "WINDOWWWWWWWWW CLOSSSSSSINGGGGG" << std::endl;
				window.close();
			}


			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::D)
				{
					sf::Vector2f pos = shape.getPosition();
					shape.setPosition(pos.x + 1, pos.y);
				}
			}

		}
		shape.move(1.f * deltaTime, 0.f);

		window.clear(sf::Color::Black);
		window.draw(shape);
		window.display();
	}
}