#ifndef TILE_H
#include <Constants.h>
#include <GameObject.h>
#include <SFML/Window.hpp>
#define TILE_H

enum Material
{
	STONE,
	DIRT,
	SAND,
};

class Tile : public GameObject
{
public:
	Tile(float x, float y, Material material);
	Material material;
	bool hasMoved;
};

#endif