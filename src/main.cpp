#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>

int main()
{
std::cout << "Working Directory: " << std::filesystem::current_path() << std::endl;
    sf::RenderWindow window(sf::VideoMode({ 400, 400 }), "My SFML");
  /*  sf::RectangleShape shape(sf::Vector2f(100,50));*/

	sf::Texture texture;
	texture.loadFromFile("./assets/main.png");

    //setup font and text
    sf::Font font;
    font.loadFromFile("./assets/OpenSans-Bold.ttf");
    sf::Text text;
    text.setFont(font);
 
    text.setString("MINECRAFT");
    text.setPosition((200.0f - text.getGlobalBounds().width / 2), 0.0f);
    

    sf::Sprite sprite(texture);
	sprite.setScale(0.1f, 0.1f); 

    //shape.setFillColor(sf::Color::Green);

    float xPos{ 0.0f };

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


            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                std::cout << "Left Mouse Button Pressed" << std::endl;
            }

        }

        sprite.setPosition(xPos, 0.0f);
        xPos+=0.001f;
        if (xPos > 400)
        {
            xPos = 0;
        }

        window.clear();
        window.draw(sprite);
        window.draw(text);
        window.display();
    }
} 