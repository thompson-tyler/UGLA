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
	void damage(int amount, sf::Vector2f knockback);
	void jump();

	bool onGround;
	bool inWater;
	bool facingRight;
	int health;
};

#endif