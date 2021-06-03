#ifndef BACKGROUNDMANAGER_H
#include <Constants.h>
#include <SFML/Window.hpp>
#define BACKGROUNDMANAGER_H

class BackgroundManager
{
public:
	BackgroundManager();
	void render(sf::RenderWindow& window, float xOff);

private:
	sf::Texture texture[4];
	sf::RectangleShape sprite[4];
};
#endif