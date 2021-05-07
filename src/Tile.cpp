#include <Tile.h>

Tile::Tile(float x, float y, Material material) :
	GameObject(x, y, sf::RectangleShape { sf::Vector2f { U_P, U_P } })
{
	this->material = material;
	this->hasMoved = false;
}