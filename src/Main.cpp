#include <Constants.h>
#include <EntityManager.h>
#include <GameObject.h>
#include <Player.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Tile.h>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIN_SIZE.x, 600), "UGLA", sf::Style::Close);
	window.setKeyRepeatEnabled(false);
	// window.setFramerateLimit(60);
	// window.setVerticalSyncEnabled(true);

	Player player;

	EntityManager eMan;
	eMan.setPlayer(player);

	sf::Clock timer;
	float renderTime = 0;

	while (window.isOpen())
	{
		// event handling
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
						case JUMP_KEY:
							player.jump();
							break;
						case DIVE_KEY:
							player.dive();
							break;
						case sf::Keyboard::Space:
							eMan.groundJump();
							break;
						case sf::Keyboard::Up:
							eMan.raiseGround();
							break;
						case sf::Keyboard::Left:
							eMan.pushTiles(-1);
							break;
						case sf::Keyboard::Right:
							eMan.pushTiles(1);
							break;
						case sf::Keyboard::Hyphen:
							eMan.zoomOut();
							break;
						case sf::Keyboard::Equal:
							eMan.zoomIn();
							break;
						case sf::Keyboard::Escape:
							window.close();
							break;
						default:
							break;
					}
					break;

				default:
					break;
			}
		}

		// update game objects
		eMan.update(timer.getElapsedTime().asSeconds());

		// render to screen at max of 60 fps
		renderTime += timer.restart().asSeconds();

		if (renderTime > FRAME_DURATION)
		{
			renderTime -= FRAME_DURATION;

			// clear window with black color
			window.clear(sf::Color(244, 233, 205));

			// render game objects
			eMan.render(window);

			// end and display frame
			window.display();
		}
	}

	return 0;
}
