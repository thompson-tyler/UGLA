#include <GameObject.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

GameObject::GameObject(float x, float y, sf::RectangleShape sprite)
{
	this->position = { x, y };
	this->velocity = { 0, 0 };

	this->sprite = sprite;
	this->size = { sprite.getSize().x, sprite.getSize().y };
	this->sprite.setOrigin(size.x / 2, size.y / 2);
}

GameObject::GameObject(float x, float y, sf::RectangleShape sprite, sf::Vector2f hitboxSize)
{
	this->position = { x, y };
	this->velocity = { 0, 0 };

	this->sprite = sprite;
	this->size = hitboxSize;
	this->sprite.setOrigin(this->sprite.getSize().x / 2, this->sprite.getSize().y / 2);
}

void GameObject::render(sf::RenderWindow& window)
{
	this->sprite.setPosition(centerAsSFMLCoords());

	window.draw(this->sprite);
}

sf::Vector2f GameObject::cornerAsSFMLCoords()
{
	return { position.x - size.x / 2, WORLD_SIZE.y - (position.y + size.y / 2) };
}

sf::Vector2f GameObject::centerAsSFMLCoords()
{
	return { position.x, WORLD_SIZE.y - position.y };
}