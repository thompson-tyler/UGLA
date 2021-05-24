#ifndef ENEMY_H
#include <Constants.h>
#include <Entity.h>
#define ENEMY_H

class Enemy : public Entity
{
public:
	Enemy(float x, float y, sf::RectangleShape sprite, int health);
	void update(float dt);
	void render(sf::RenderWindow& window);
	void setTarget(Entity* target);
	void moveRight(float dt);
	void moveLeft(float dt);

private:
	Entity* target;
};

#endif