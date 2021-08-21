#include <BackgroundManager.h>
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
	sf::RenderWindow window(sf::VideoMode(WIN_SIZE.x, WIN_SIZE.y), "UGLA", sf::Style::Close);
	window.setKeyRepeatEnabled(false);
	// window.setFramerateLimit(60);
	// window.setVerticalSyncEnabled(true);

	Player player;

	EntityManager eMan;
	eMan.setPlayer(player);

	BackgroundManager bMan;

	sf::Clock timer;
	float renderTime = 0;

	bool paused = false;

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
						case GROUND_JUMP_KEY:
							eMan.groundJump();
							break;
						case RAISE_GROUND_KEY:
							eMan.raiseGround();
							break;
						case PUSH_GROUND_LEFT_KEY:
							eMan.pushTiles(-1);
							break;
						case PUSH_GROUND_RIGHT_KEY:
							eMan.pushTiles(1);
							break;
						case ZOOM_OUT_KEY:
							eMan.zoomOut();
							break;
						case ZOOM_IN_KEY:
							eMan.zoomIn();
							break;
						case EXIT_KEY:
							window.close();
							break;
						case PAUSE_KEY:
							paused = !paused;
							break;
						default:
							break;
					}
					break;

				default:
					break;
			}
		}

		if (!paused)
		{
			// update game objects
			eMan.update(timer.getElapsedTime().asSeconds());

			// render to screen at max of 60 fps
			renderTime += timer.restart().asSeconds();

			if (renderTime > FRAME_DURATION)
			{
				renderTime -= FRAME_DURATION;

				// clear window with background color
				window.clear(BACKGROUND_COLOR);

				bMan.render(window, (WORLD_SIZE.x / 2 - player.position.x) * 0.01f);

				// render game objects
				eMan.render(window);

				// end and display frame
				window.display();
			}
		}
		else
		{
			timer.restart();
		}
	}

	return 0;
}
