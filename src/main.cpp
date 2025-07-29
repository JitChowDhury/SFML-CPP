#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 400, 400 }), "My SFML");
    sf::RectangleShape shape(sf::Vector2f(100,50));
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::W)
                {

                std::cout << "A Key is Pressed" << std::endl;
                }
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}