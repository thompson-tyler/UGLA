#ifndef PLAYER_H
#include <Constants.h>
#include <Entity.h>
#define PLAYER_H

class Player : public Entity
{
public:
	Player();
	void render(sf::RenderWindow& window);
	void update(float dt);
	void moveRight(float dt);
	void moveLeft(float dt);
	void jump();
	void dive();
	bool isDiving;

private:
	bool moving;
	sf::Clock animClock;
};

#endif