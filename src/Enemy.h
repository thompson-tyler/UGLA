#ifndef ENEMY_H
#include <Constants.h>
#include <Entity.h>
#define ENEMY_H

class Enemy : public Entity
{
public:
	Enemy(float x, float y, sf::RectangleShape sprite);
	void update(float dt);
	void render(sf::RenderWindow& window);
	void setTarget(Entity* target);
	void moveRight(float dt);
	void moveLeft(float dt);
	void jump()
	{
		if (onGround or inWater)
		{
			velocity.y = JUMP_VEL;
		}
	}

private:
	Entity* target;
};

#endif