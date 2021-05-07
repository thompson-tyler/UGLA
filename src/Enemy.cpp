#include <Enemy.h>
#include <Entity.h>
#include <SFML/Graphics.hpp>
#include <cmath>

Enemy::Enemy(float x, float y, sf::RectangleShape sprite) :
	Entity(x, y, sprite)
{
	this->sprite.setFillColor(sf::Color::Red);
	this->health = 100;
}

void Enemy::update(float dt)
{
	// apply gravity
	velocity.y -= G * dt;
	if (velocity.y < -MAX_FALL_SPEED)
		velocity.y = -MAX_FALL_SPEED;

	if (velocity.x > 0)
		velocity.x -= 0.5 * HORIZONTAL_ACCEL * dt;
	else if (velocity.x < 0)
		velocity.x += 0.5 * HORIZONTAL_ACCEL * dt;

	// stop if vel is very small
	if (abs(velocity.x) < HORIZONTAL_ACCEL * dt / 2)
		velocity.x = 0;

	if (inWater)
	{
		velocity.x *= 0.9;
		velocity.y *= 0.9;
	}

	position += velocity * dt;

	if (position.x > WORLD_SIZE.x - size.x / 2)
	{
		position.x = WORLD_SIZE.x - size.x / 2;
		velocity.x = 0;
	}
	else if (position.x < size.x / 2)
	{
		position.x = size.x / 2;
		velocity.x = 0;
	}

	if (position.y < size.y / 2)
	{
		position.y = size.y / 2;
		velocity.y = 0;
	}
}

void Enemy::render(sf::RenderWindow& window)
{
	this->sprite.setPosition(cornerAsSFMLCoords());

	int r = -health / 100.f * 255;
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;

	int g = health / 100.f * 255;
	if (g < 0)
		g = 0;
	if (g > 255)
		g = 255;
	this->sprite.setFillColor(sf::Color(r, g, 0));

	window.draw(this->sprite);
}