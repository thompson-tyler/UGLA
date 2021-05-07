#ifndef ENTITY_H
#include <Constants.h>
#include <GameObject.h>
#include <SFML/Window.hpp>
#include <Tile.h>
#define ENTITY_H

class Entity : public GameObject
{
public:
	Entity(float x, float y, sf::RectangleShape sprite);
	void update(float dt);
	bool onGround;
	bool inWater;
};

#endif