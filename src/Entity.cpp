#include <Entity.h>
#include <GameObject.h>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Entity::Entity(float x, float y, sf::RectangleShape sprite) :
	GameObject(x, y, sprite)
{
	onGround = false;
	inWater = false;
	facingRight = true;
}

Entity::Entity(float x, float y, sf::RectangleShape sprite, sf::Vector2f hitboxSize) :
	GameObject(x, y, sprite, hitboxSize)
{
	onGround = false;
	inWater = false;
	facingRight = true;
}

void Entity::render(sf::RenderWindow& window)
{
	this->sprite.setScale((facingRight ? 1.f : -1.f), 1.f);
	this->sprite.setPosition(centerAsSFMLCoords());

	window.draw(this->sprite);
}

void Entity::jump()
{
	if (onGround)
		velocity.y = JUMP_VEL;

	else if (inWater)
		velocity.y = JUMP_VEL / 2;
}

void Entity::damage(int amount, sf::Vector2f knockback)
{
	health -= amount;
	velocity += knockback;
}