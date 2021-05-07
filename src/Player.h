#ifndef PLAYER_H
#include <Constants.h>
#include <Entity.h>
#include <SFML/Window.hpp>
#include <Tile.h>
#define PLAYER_H

class Player : public Entity
{
public:
	Player();
	void update(float dt);
	void moveRight(float dt);
	void moveLeft(float dt);
	void jump();
	void dive();
	bool isDiving;
	bool facingRight;
};

#endif