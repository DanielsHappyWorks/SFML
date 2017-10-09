#include "ResourceHolder.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

enum class TexturesID {
	Landscape,
	Airplane
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 400), "Resource Management");
	window.setFramerateLimit(20);

	//try load resources
	ResourceHolder<sf::Texture, TexturesID> textures;
	try {
		textures.load(TexturesID::Landscape, "Media/Textures/Desert.png");
		textures.load(TexturesID::Airplane, "Media/Textures/Eagle.png");
	}
	catch (std::runtime_error& e) {
		std::cout << "Exception: " << e.what() << std::endl;
		return 1;
	}

	sf::Sprite landscape(textures.get(TexturesID::Landscape));
	sf::Sprite airplane(textures.get(TexturesID::Airplane));
	airplane.setPosition(200.f, 200.f);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed || event.type == sf::Event::Closed) {
				return 0;
			}
		}


		window.clear();
		window.draw(landscape);
		window.draw(airplane);
		window.display();
	}
}