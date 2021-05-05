#ifndef PLAYER_H
#include <Constants.h>
#include <GameObject.h>
#include <SFML/Window.hpp>
#include <Tile.h>
#define PLAYER_H

class Player : public GameObject
{
public:
	Player();
	void update(float dt);
	void moveRight(float dt);
	void moveLeft(float dt);
	void jump();
	void dive();
	bool onGround;
	bool isDiving;
	bool facingRight;

private:
};

#endif