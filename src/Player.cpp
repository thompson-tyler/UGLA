#include <Entity.h>
#include <Player.h>
#include <SFML/Graphics.hpp>
#include <cmath>

Player::Player() :
	Entity(WORLD_SIZE.x / 2, WORLD_SIZE.y * 0.5, sf::RectangleShape { PLAYER_SIZE })
{
	isDiving = false;
	moving = false;
	this->health = 20;

	// this->sprite.setFillColor(PLAYER_COLOR);
	texture.loadFromFile("content/mario_sheet.png");
	rectSourceSprite = { 0, 0, 16, 16 };

	this->sprite.setTexture(&texture);
	sprite.setTextureRect(rectSourceSprite);
}

void Player::render(sf::RenderWindow& window)
{
	if (!onGround)
	{
		if (isDiving)
			rectSourceSprite.left = 80;
		else
			rectSourceSprite.left = 64;
	}
	else if (!moving)
	{
		rectSourceSprite.left = 0;
	}
	else
	{
		if (animClock.getElapsedTime().asSeconds() > 0.1f)
		{
			rectSourceSprite.left += 16;
			if (rectSourceSprite.left > 48)
				rectSourceSprite.left = 16;

			animClock.restart();
		}
	}

	sprite.setTextureRect(rectSourceSprite);
	this->sprite.setScale((facingRight ? 1.f : -1.f), 1.f);
	this->sprite.setPosition(centerAsSFMLCoords());

	window.draw(this->sprite);
}

void Player::moveRight(float dt)
{
	// apply accel
	velocity.x += HORIZONTAL_ACCEL * dt;

	// limit speed
	if (velocity.x > MAX_HORIZONTAL_SPEED)
		velocity.x = MAX_HORIZONTAL_SPEED;
}

void Player::moveLeft(float dt)
{
	// apply accel
	velocity.x -= HORIZONTAL_ACCEL * dt;

	// limit speed
	if (velocity.x < -MAX_HORIZONTAL_SPEED)
		velocity.x = -MAX_HORIZONTAL_SPEED;
}

void Player::jump()
{
	if ((onGround or inWater) and !isDiving)
	{
		velocity.y = JUMP_VEL;
	}
}

void Player::dive()
{
	// enable diving if in air
	isDiving = !onGround;
}

void Player::update(float dt)
{
	// 		HORIZONTAL MOVEMENT

	moving = false;
	if (sf::Keyboard::isKeyPressed(MOVE_RIGHT_KEY))
	{
		if (!isDiving)
		{
			moveRight(dt);
			moving = true;
		}
		facingRight = true;
	}
	if (sf::Keyboard::isKeyPressed(MOVE_LEFT_KEY))
	{
		if (!isDiving)
		{
			moveLeft(dt);
			moving = true;
		}
		facingRight = false;
	}

	// move to slow down if not pressing move left or right keys
	if (!moving)
	{
		if (velocity.x > 0)
			velocity.x -= HORIZONTAL_ACCEL * dt;
		else if (velocity.x < 0)
			velocity.x += HORIZONTAL_ACCEL * dt;

		// stop player if vel is very small
		if (abs(velocity.x) < HORIZONTAL_ACCEL * dt / 2)
			velocity.x = 0;
	}

	// apply gravity
	velocity.y -= (isDiving ? DIVE_COEFF : 1) * G * dt;
	if (velocity.y < -MAX_FALL_SPEED)
		velocity.y = -MAX_FALL_SPEED;

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

	if (position.y < size.y / 2)
	{
		position.y = size.y / 2;
		velocity.y = 0;
	}

	if (onGround)
	{
		isDiving = false;
	}
}