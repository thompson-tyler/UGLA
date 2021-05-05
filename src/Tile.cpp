#include <Tile.h>

Tile::Tile(float x, float y, Material material) :
	GameObject(x, y, sf::RectangleShape { sf::Vector2f { U_P, U_P } })
{
	this->material = material;
	this->hasMoved = false;

	switch (material)
	{
		case STONE:
			sprite.setFillColor(sf::Color(75, 78, 75));
			break;
		case DIRT:
			sprite.setFillColor(sf::Color::Red);
			break;
		case SAND:
			sprite.setFillColor(sf::Color(218, 181, 107));
			break;
		default:
			sprite.setFillColor(sf::Color::White);
			break;
	}
}