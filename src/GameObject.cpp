#include <GameObject.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

GameObject::GameObject(float x, float y, sf::RectangleShape sprite)
{
	this->position = { x, y };
	this->sprite = sprite;
	this->size = { sprite.getSize().x, sprite.getSize().y };
	this->velocity = { 0, 0 };
}

void GameObject::render(sf::RenderWindow& window)
{
	this->sprite.setPosition(cornerAsSFMLCoords());

	// int r = -velocity.y * 100;
	// if (r < 0) r = 0;
	// if (r > 255) r = 255;

	// int g = velocity.y * 30;
	// if (g < 0) g = 0;
	// if (g > 255) g = 255;
	// this->sprite.setFillColor(sf::Color(r, g, 0));

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