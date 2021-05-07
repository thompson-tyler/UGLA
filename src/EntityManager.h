#ifndef EntityManager_H
#include <Constants.h>
#include <Player.h>
#include <SFML/Window.hpp>
#include <Tile.h>
#define EntityManager_H

class EntityManager
{
public:
	EntityManager();
	~EntityManager();
	void render(sf::RenderWindow& window);
	void update(float dt);
	void setPlayer(Player& player);
	void groundJump();
	void initRipple();
	void raiseGround();
	void pushTiles(int direction);
	void zoomIn();
	void zoomOut();

	Player* player;
	Tile* tiles[TILES_Y][TILES_X];
	void doBlockUpdates();

private:
	float updateTimer, blockGravTimer;
	void initTileColors();
	void checkPlayerTileCollision();
	bool playerOnScreen();
	bool validPos(int x, int y);
	int signOf(int n);
	float clamp(float n, float min, float max);
	void moveTileTo(int xi, int yi, int xf, int yf);
	void updateRipple();

	struct Ripple
	{
		int x, y, offset;
	};
	Ripple currRipple;

	float viewScale;
};

#endif