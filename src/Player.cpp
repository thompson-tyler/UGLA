#include <Entity.h>
#include <Player.h>
#include <SFML/Graphics.hpp>
#include <cmath>

Player::Player() :
	Entity(WORLD_SIZE.x / 2, WORLD_SIZE.y / 2, sf::RectangleShape(PLAYER_SPRITE_SIZE), PLAYER_HITBOX_SIZE)
{
	isDiving = false;
	moving = false;
	this->health = 20;

	// this->sprite.setFillColor(PLAYER_COLOR);
	texture.loadFromFile("content/adventurer_sheet.png");
	rectSourceSprite = { 0, 0, (int)PLAYER_SPRITE_SIZE.x, (int)PLAYER_SPRITE_SIZE.y };

	this->sprite.setTexture(&texture);
	sprite.setTextureRect(rectSourceSprite);
	sprite.setPosition(centerAsSFMLCoords());
}

void Player::render(sf::RenderWindow& window)
{
	if (!onGround)
	{
		if (isDiving)
		{
			rectSourceSprite.left = 0;
			rectSourceSprite.top = 0;
		}
		else
		{
			rectSourceSprite.left = 0;
			rectSourceSprite.top = 0;
		}
	}
	// runnning animation
	else if (moving)
	{
		rectSourceSprite.top = PLAYER_SPRITE_SIZE.y;
		if (animClock.getElapsedTime().asSeconds() > 0.1f)
		{
			rectSourceSprite.left += PLAYER_SPRITE_SIZE.x;

			animClock.restart();
		}
		if (rectSourceSprite.left >= PLAYER_SPRITE_SIZE.x * 6)
			rectSourceSprite.left = 0;
	}
	// idle animation
	else
	{
		rectSourceSprite.top = 0;
		if (animClock.getElapsedTime().asSeconds() > 0.25f)
		{
			rectSourceSprite.left += PLAYER_SPRITE_SIZE.x;

			animClock.restart();
		}
		if (rectSourceSprite.left >= PLAYER_SPRITE_SIZE.x * 4)
			rectSourceSprite.left = 0;
	}

	sprite.setTextureRect(rectSourceSprite);
	this->sprite.setScale((facingRight ? 1.f : -1.f), 1.f);

	// interpolation coefficient: higher will keep sprite closer to actual pos but be more choppy
	float interp = 0.5f;

	sf::Vector2f newPos = { centerAsSFMLCoords().x * interp + sprite.getPosition().x * (1.f - interp), centerAsSFMLCoords().y * interp + sprite.getPosition().y * (1.f - interp) };

	this->sprite.setPosition(newPos);

	window.draw(this->sprite);

	// debug hitbox rendering
	sf::RectangleShape hitboxOutline(this->size);
	hitboxOutline.setOrigin(size.x / 2, size.y / 2);
	hitboxOutline.setPosition(centerAsSFMLCoords());
	hitboxOutline.setOutlineThickness(1);
	hitboxOutline.setOutlineColor(sf::Color::Red);
	hitboxOutline.setFillColor(sf::Color::Transparent);

	window.draw(hitboxOutline);
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
	if (!onGround and !inWater)
		isDiving = true;
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

	if (onGround or inWater)
	{
		isDiving = false;
	}
}