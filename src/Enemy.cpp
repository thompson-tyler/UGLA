#include <Enemy.h>
#include <Entity.h>
#include <SFML/Graphics.hpp>
#include <cmath>

Enemy::Enemy(float x, float y, sf::RectangleShape sprite, int health) :
	Entity(x, y, sprite)
{
	this->sprite.setFillColor(sf::Color::Cyan);
	this->health = health;
	this->maxHealth = health;
	this->target = nullptr;
}

void Enemy::setTarget(Entity* target)
{
	this->target = target;
}

void Enemy::moveRight(float dt)
{
	if (velocity.x < MAX_HORIZONTAL_SPEED)
	{
		velocity.x += 0.2f * HORIZONTAL_ACCEL * dt;

		// limit speed
		if (velocity.x > 0.5f * MAX_HORIZONTAL_SPEED)
			velocity.x = 0.5f * MAX_HORIZONTAL_SPEED;
	}
}

void Enemy::moveLeft(float dt)
{
	if (velocity.x > -MAX_HORIZONTAL_SPEED)
	{
		velocity.x -= 0.2f * HORIZONTAL_ACCEL * dt;

		// limit speed
		if (velocity.x < 0.5f * -MAX_HORIZONTAL_SPEED)
			velocity.x = 0.5f * -MAX_HORIZONTAL_SPEED;
	}
}

void Enemy::update(float dt)
{
	// 		HORIZONTAL MOVEMENT

	bool moving = false;
	int targetDist = 16 * U_P;
	double dist = abs(position.x - target->position.x);
	if (abs(dist - targetDist) > 2 * U_P)
	{
		moving = true;
		if (position.x < target->position.x)
		{
			if (dist > targetDist)
			{
				moveRight(dt);
			}
			else
			{
				moveLeft(dt);
			}
		}
		else
		{
			if (dist > targetDist)
			{
				moveLeft(dt);
			}
			else
			{
				moveRight(dt);
			}
		}
	}

	// apply gravity
	velocity.y -= G * dt;
	if (velocity.y < -MAX_FALL_SPEED)
		velocity.y = -MAX_FALL_SPEED;

	if (!moving)
	{
		if (velocity.x > 0)
			velocity.x -= 0.5 * HORIZONTAL_ACCEL * dt;
		else if (velocity.x < 0)
			velocity.x += 0.5 * HORIZONTAL_ACCEL * dt;

		// stop if vel is very small
		if (abs(velocity.x) < HORIZONTAL_ACCEL * dt / 2)
			velocity.x = 0;
	}

	if (inWater)
	{
		velocity.x *= 0.9;
		velocity.y *= 0.9;
	}

	position += velocity * dt;

	// keep in world bounds

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

	if (position.y > WORLD_SIZE.y - size.y / 2)
	{
		position.y = WORLD_SIZE.y - size.y / 2;
		velocity.y = 0;
	}
	else if (position.y < size.y / 2)
	{
		position.y = size.y / 2;
		velocity.y = 0;
	}
}

void Enemy::render(sf::RenderWindow& window)
{
	this->sprite.setPosition(centerAsSFMLCoords());

	window.draw(this->sprite);

	sf::RectangleShape healthBarBackground({ HEALTH_BAR_WIDTH, 5 });
	healthBarBackground.setFillColor(sf::Color::White);
	healthBarBackground.setOrigin(healthBarBackground.getSize().x / 2, healthBarBackground.getSize().y / 2);
	sf::Vector2f barPos = centerAsSFMLCoords();
	barPos.y -= this->size.y / 2 + 20;
	healthBarBackground.setPosition(barPos);

	window.draw(healthBarBackground);

	sf::RectangleShape healthBar({ (1.f * this->health / this->maxHealth) * HEALTH_BAR_WIDTH, 5 });
	healthBar.setOutlineColor(sf::Color::Black);
	healthBar.setFillColor(sf::Color::Red);
	healthBar.setOrigin(healthBar.getSize().x / 2, healthBar.getSize().y / 2);
	barPos = centerAsSFMLCoords();
	barPos.y -= this->size.y / 2 + 20;
	barPos.x += (healthBar.getSize().x - HEALTH_BAR_WIDTH) * 0.5f;
	healthBar.setPosition(barPos);

	window.draw(healthBar);

	sf::RectangleShape healthBarOutline({ HEALTH_BAR_WIDTH, 5 });
	healthBarOutline.setOutlineColor(sf::Color::Black);
	healthBarOutline.setOutlineThickness(1);
	healthBarOutline.setFillColor(sf::Color::Transparent);
	healthBarOutline.setOrigin(healthBarOutline.getSize().x / 2, healthBarOutline.getSize().y / 2);
	barPos = centerAsSFMLCoords();
	barPos.y -= this->size.y / 2 + 20;
	healthBarOutline.setPosition(barPos);

	window.draw(healthBarOutline);
}