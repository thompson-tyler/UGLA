#ifndef EntityManager_H
#include <Constants.h>
#include <Enemy.h>
#include <Entity.h>
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

	Enemy* enemy;
	Player* player;
	Tile* tiles[TILES_Y][TILES_X];
	void doBlockUpdates();

private:
	float updateTimer, blockGravTimer;
	void initTileColors();
	void checkEntityTileCollision(Entity* entity);
	void checkPlayerTileCollision();
	bool entityOnScreen(Entity* entity);
	bool validPos(int x, int y);
	int signOf(int n);
	bool earthBendable(Tile* tile);
	float clamp(float n, float min, float max);
	void switchTiles(int x1, int y1, int x2, int y2);
	void updateRipple();

	struct Ripple
	{
		int x, y, offset;
	};
	Ripple currRipple;

	float viewScale;
};

#endif