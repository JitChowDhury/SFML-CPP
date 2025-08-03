//#include "Game.h"
//
//int main()
//{
//	Game game;
//	game.run();
//}
#include<iostream>
#include <filesystem>
#include<SFML\Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1240, 720), "TEST SFML");
	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("assets/player.png"))
	{
		std::cout << "PLayer Texture Not Found" << std::endl;
	
		return -1;
	}


	sf::Sprite playerSprite;
	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(sf::Vector2f(400.f, 500.f));



	
		while (window.isOpen())
		{
			sf::Event event;
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
					{
						window.close();
					}
				}



				window.clear();
				window.draw(playerSprite);
				window.display();
		}
	}
