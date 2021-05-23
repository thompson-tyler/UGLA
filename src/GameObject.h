#ifndef GAMEOBJECT_H
#include <Constants.h>
#include <SFML/Window.hpp>
#define GAMEOBJECT_H

class GameObject
{
public:
	GameObject(float x, float y, sf::RectangleShape sprite);
	GameObject(float x, float y, sf::RectangleShape sprite, sf::Vector2f hitboxSize);

	void render(sf::RenderWindow& window);
	sf::Vector2f cornerAsSFMLCoords();
	sf::Vector2f centerAsSFMLCoords();

	sf::Vector2f size;
	sf::Vector2f position, velocity;
	sf::RectangleShape sprite;
};

#endif