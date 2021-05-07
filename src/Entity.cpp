#include <Entity.h>
#include <GameObject.h>
#include <SFML/Graphics.hpp>
#include <cmath>

Entity::Entity(float x, float y, sf::RectangleShape sprite) :
	GameObject(x, y, sprite)
{
	onGround = false;
	inWater = false;
	facingRight = true;
}

void Entity::damage(int amount, sf::Vector2f knockback)
{
	health -= amount;
	velocity += knockback;
}