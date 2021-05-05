#include <EntityManager.h>
#include <cmath>
#include <iostream>

EntityManager::EntityManager()
{
	for (int y = 0; y < WIN_TILES_Y; y++)
	{
		for (int x = 0; x < WIN_TILES_X; x++)
		{
			// if (y < 2 + pow(x - WIN_TILES_X / 2, 2) / 30)
			// if (y < 10 or (y > x * x / 100 + 10 and y < x * x / 20 and y < WIN_TILES_Y - 5 and x > 30))
			if (y < 8 * sin(x / 6.f) + 16)
			// if (y < 20)
			{
				if (y > 5 and y < 15)
					tiles[y][x] = new Tile { U_P * (x + 0.5f), U_P * (y + 0.5f), SAND };
				else
					tiles[y][x] = new Tile { U_P * (x + 0.5f), U_P * (y + 0.5f), STONE };
			}
			else
			{
				tiles[y][x] = nullptr;
			}
		}
	}
	updateTimer = 0;
	blockGravTimer = 0;
	currRipple = { 0, 0, -1 };
	viewScale = 1;
}

EntityManager::~EntityManager()
{
	for (int y = 0; y < WIN_TILES_Y; y++)
	{
		for (int x = 0; x < WIN_TILES_X; x++)
		{
			delete tiles[y][x];
		}
	}
}

void EntityManager::zoomIn()
{
	viewScale -= 0.1;
	if (viewScale < 0.2)
	{
		viewScale = 0.2;
	}
}

void EntityManager::zoomOut()
{
	viewScale += 0.1;
	if (viewScale > 1)
	{
		viewScale = 1;
	}
}

void EntityManager::render(sf::RenderWindow& window)
{
	sf::Vector2f viewSize { WIN_SIZE.x * viewScale, WIN_SIZE.y * viewScale };
	sf::Vector2f viewCenter = player->centerAsSFMLCoords();

	if (viewCenter.x < viewSize.x / 2)
		viewCenter.x = viewSize.x / 2;
	else if (viewCenter.x > WIN_SIZE.x - viewSize.x / 2)
		viewCenter.x = WIN_SIZE.x - viewSize.x / 2;

	if (viewCenter.y < viewSize.y / 2)
		viewCenter.y = viewSize.y / 2;
	else if (viewCenter.y > WIN_SIZE.y - viewSize.y / 2)
		viewCenter.y = WIN_SIZE.y - viewSize.y / 2;

	sf::View view { viewCenter, viewSize };

	window.setView(view);

	for (int y = 0; y < WIN_TILES_Y; y++)
	{
		for (int x = 0; x < WIN_TILES_X; x++)
		{
			if (tiles[y][x] != nullptr)
			{
				tiles[y][x]->render(window);
			}
		}
	}
	player->render(window);
}

void EntityManager::update(float dt)
{
	updateTimer += dt;
	blockGravTimer += dt;

	while (updateTimer > UPDATE_DURATION)
	{
		player->update(UPDATE_DURATION);
		checkPlayerTileCollision();

		updateTimer -= UPDATE_DURATION;
	}

	while (blockGravTimer > GRAV_CHECK_DURATION)
	{
		doBlockUpdates();

		updateRipple();

		blockGravTimer -= GRAV_CHECK_DURATION;
	}
}

void EntityManager::setPlayer(Player& player)
{
	this->player = &player;
}

void EntityManager::groundJump()
{
	if (player->onGround)
	{
		// get tile selection under player
		int minTileX = (player->position.x - player->size.x / 2) / U_P;
		if (minTileX < 0)
			minTileX = 0;

		int maxTileX = (player->position.x + player->size.x) / U_P;
		if (maxTileX > WIN_TILES_X)
			maxTileX = WIN_TILES_X;

		int minTileY = (player->position.y - player->size.y) / U_P - GROUND_JUMP_COL_HEIGHT;
		if (minTileY < 1)
			minTileY = 1;

		int maxTileY = (player->position.y - player->size.y / 2) / U_P;
		if (maxTileY > WIN_TILES_Y)
			maxTileY = WIN_TILES_Y;

		for (int y = minTileY; y < maxTileY; y++)
		{
			for (int x = minTileX; x < maxTileX; x++)
			{
				if (validPos(x, y) and tiles[y][x] != nullptr)
				{
					tiles[y][x]->velocity.y = GROUND_JUMP_COL_HEIGHT + (maxTileY - y);
				}
			}
		}
		player->velocity.y = JUMP_VEL * GROUND_JUMP_COEFF;
	}
}

void EntityManager::initRipple()
{
	if (currRipple.offset == -1 and player->velocity.y < -MAX_FALL_SPEED * 0.8)
	{
		int originX = player->position.x / U_P;
		int originY = (player->position.y - player->size.y / 2) / U_P;
		int initOff = (player->size.x / 2) / U_P + 2;

		if (validPos(originX, originY))
			currRipple = { originX, originY, initOff };
	}
}

void EntityManager::updateRipple()
{
	// if active ripple
	if (currRipple.offset != -1)
	{
		for (int sign : { -1, 1 })
		{
			int x = currRipple.x + sign * currRipple.offset;

			if (!validPos(x, currRipple.y))
				continue;

			int maxTileY = currRipple.y;

			// base tile is not ground, iterate down to find surface
			if (tiles[maxTileY][x] == nullptr)
			{
				while (validPos(x, maxTileY - 1) and tiles[maxTileY][x] == nullptr)
				{
					maxTileY--;
				}
			}
			// base tile is ground, iterate up to surface
			else
			{
				while (validPos(x, maxTileY + 1) and tiles[maxTileY + 1][x] != nullptr)
				{
					maxTileY++;
				}
			}

			int minTileY = maxTileY - (RIPPLE_THICKNESS - 1);
			if (minTileY < 1)
				minTileY = 1;

			for (int y = minTileY; y <= maxTileY; y++)
			{
				if (tiles[y][x] != nullptr)
				{
					tiles[y][x]->velocity.y = 4;
				}
			}
		}
		currRipple.offset++;

		if (currRipple.offset > RIPPLE_RADIUS)
		{
			currRipple.offset = -1;
		}
	}
}

void EntityManager::raiseGround()
{
	if (player->onGround)
	{
		int sign = (player->facingRight ? 1 : -1);

		int centerX = (player->position.x + player->size.x / 2) / U_P + sign * 8;

		// get tile selection in front of player
		int minTileX = centerX - RAISE_BOULDER_SIZE / 2;
		if (minTileX >= WIN_TILES_X)
			minTileX = WIN_TILES_X;
		else if (minTileX < 0)
			minTileX = 0;

		int maxTileX = centerX + RAISE_BOULDER_SIZE / 2;
		if (maxTileX >= WIN_TILES_X)
			maxTileX = WIN_TILES_X - 1;
		else if (maxTileX < 0)
			maxTileX = 0;

		for (int x = minTileX; x <= maxTileX; x++)
		{
			int maxTileY = player->position.y / U_P;

			if (!validPos(x, maxTileY))
				continue;

			// base tile is not ground, iterate down to find surface
			if (tiles[maxTileY][x] == nullptr)
			{
				while (validPos(x, maxTileY - 1) and tiles[maxTileY][x] == nullptr)
				{
					maxTileY--;
				}
			}
			// base tile is ground, iterate up to surface
			else
			{
				while (validPos(x, maxTileY + 1) and tiles[maxTileY + 1][x] != nullptr)
				{
					maxTileY++;
				}
			}

			int playerHeightOff = (player->position.y - player->size.y / 2) / U_P - maxTileY;

			if (playerHeightOff < 0)
				playerHeightOff = 0;

			// height of raised tiles is equal to width of effect
			int minTileY = maxTileY - (RAISE_BOULDER_SIZE - 1);
			if (minTileY < 1)
				minTileY = 1;

			for (int y = minTileY; y <= maxTileY; y++)
			{
				if (validPos(x, y) and tiles[y][x] != nullptr)
				{
					tiles[y][x]->velocity.y = (RAISE_BOULDER_SIZE + 3) + playerHeightOff;
				}
			}
		}
	}
}

// direction: 1 if pushing right, -1 if pushing left
void EntityManager::pushTiles(int direction)
{
	// get tile selection in front of player
	int minTileX = player->position.x / U_P;

	int maxTileX = minTileX + direction * 16;

	int minTileY = (player->position.y - player->size.y / 2) / U_P;
	if (minTileY < 1)
		minTileY = 1;

	int maxTileY = minTileY + 8;
	if (maxTileY > WIN_TILES_Y)
		maxTileY = WIN_TILES_Y;

	for (int y = minTileY; y < maxTileY; y++)
	{
		for (int x = minTileX; x != maxTileX; x += direction)
		{
			if (validPos(x, y) and tiles[y][x] != nullptr)
			{
				tiles[y][x]->velocity = { direction * PUSH_VELOCITY, 0 };
			}
		}
	}
}

bool EntityManager::playerOnScreen()
{
	return (player->position.x - player->size.x / 2 >= 0 and player->position.x + player->size.x / 2 <= WIN_SIZE.x) and (player->position.y - player->size.y / 2 >= 0 and player->position.y + player->size.y / 2 <= WIN_SIZE.y);
}

bool EntityManager::validPos(int x, int y)
{
	return (0 <= x and x < WIN_TILES_X and 0 <= y and y < WIN_TILES_Y);
}

int EntityManager::signOf(int n)
{
	return (n > 0 ? 1 : -1);
}

void EntityManager::moveTileTo(int xi, int yi, int xf, int yf)
{
	if (validPos(xi, yi) and validPos(xf, yf) and tiles[yi][xi] != nullptr and tiles[yf][xf] == nullptr)
	{
		tiles[yi][xi]->position.x += (xf - xi) * U_P;
		tiles[yi][xi]->position.y += (yf - yi) * U_P;
		tiles[yi][xi]->hasMoved = true;
		tiles[yf][xf] = tiles[yi][xi];
		tiles[yi][xi] = nullptr;
	}
}

void EntityManager::doBlockUpdates()
{
	for (int y = 1; y < WIN_TILES_Y; y++)
	{
		for (int x = 0; x < WIN_TILES_X; x++)
		{
			if (tiles[y][x] != nullptr)
			{
				tiles[y][x]->hasMoved = false;
			}
		}
	}

	// gravity check
	for (int y = 1; y < WIN_TILES_Y; y++)
	{
		for (int x = 0; x < WIN_TILES_X; x++)
		{
			Tile* currTile = tiles[y][x];
			if (currTile != nullptr and currTile->velocity.x == 0 and currTile->velocity.y <= 0)
			{
				// apply gravity if below tile is empty or falling
				if (tiles[y - 1][x] == nullptr or tiles[y - 1][x]->velocity.y < 0)
				{
					tiles[y][x]->velocity.y--;
				}
			}
		}
	}

	// stopping check
	for (int y = 1; y < WIN_TILES_Y; y++)
	{
		for (int x = 0; x < WIN_TILES_X; x++)
		{
			Tile* currTile = tiles[y][x];
			if (currTile != nullptr)
			{
				// check horizontal stopping
				if (currTile->velocity.x != 0)
				{
					int sign = signOf(currTile->velocity.x);

					if (validPos(x + sign, y))
					{
						if (tiles[y][x + sign] != nullptr and (tiles[y][x + sign]->velocity.x == 0 or signOf(tiles[y][x + sign]->velocity.x) != sign))
						{
							currTile->velocity.x = 0;
						}
					}
					else
					{
						currTile->velocity.x = 0;
					}
				}
				// check vertical stopping
				else if (currTile->velocity.y != 0)
				{
					int sign = signOf(currTile->velocity.y);

					if (validPos(x, y + sign))
					{
						if (tiles[y + sign][x] != nullptr and (tiles[y + sign][x]->velocity.y == 0 or signOf(tiles[y + sign][x]->velocity.y) != sign))
						{
							if (sign == 1)
								currTile->velocity.y -= sign;
							else
								currTile->velocity.y = 0;
						}
					}
					else
					{
						currTile->velocity.y -= sign;
					}
				}
			}
		}
	}

	// movement
	bool movedTile;
	do
	{
		movedTile = false;

		for (int y = 1; y < WIN_TILES_Y; y++)
		{
			for (int x = 0; x < WIN_TILES_X; x++)
			{
				Tile* currTile = tiles[y][x];
				if (currTile != nullptr and !currTile->hasMoved)
				{
					// horizontal movement
					if (currTile->velocity.x != 0)
					{
						int sign = signOf(currTile->velocity.x);

						// if tile can physically move to desired side, move it
						if (validPos(x + sign, y) and tiles[y][x + sign] == nullptr)
						{
							currTile->velocity.x -= sign;
							moveTileTo(x, y, x + sign, y);
							movedTile = true;
						}
					}
					// vertical movement
					else if (currTile->velocity.y != 0)
					{
						int sign = signOf(currTile->velocity.y);

						// if tile can physically move to desired side, move it
						if (validPos(x, y + sign) and tiles[y + sign][x] == nullptr)
						{
							currTile->velocity.y -= sign;
							moveTileTo(x, y, x, y + sign);
							movedTile = true;
						}
					}
					// sand movement -> fall to diagonals if they're empty
					else if (currTile->material == SAND)
					{
						for (int sign : { -1, 1 })
						{
							if (validPos(x + sign, y - 1) and tiles[y - 1][x + sign] == nullptr)
							{
								moveTileTo(x, y, x + sign, y - 1);
							}
						}
					}
				}
			}
		}
	} while (movedTile);
}

void EntityManager::checkPlayerTileCollision()
{
	Tile* currTile;
	float dx, dy, dxMin, dyMin;

	player->onGround = false;

	// only check a small region around player for collisions
	int minTileX = (player->position.x - player->size.x / 2) / U_P;
	if (minTileX < 0)
		minTileX = 0;
	int maxTileX = (player->position.x + player->size.x) / U_P;
	if (maxTileX > WIN_TILES_X)
		maxTileX = WIN_TILES_X;
	int minTileY = (player->position.y - player->size.y / 2) / U_P;
	if (minTileY < 0)
		minTileY = 0;
	int maxTileY = (player->position.y + player->size.y) / U_P;
	if (maxTileY > WIN_TILES_Y)
		maxTileY = WIN_TILES_Y;

	if (playerOnScreen())
	{
		// check if player is buried in many tiles
		int overlappingTiles = 0;
		for (int y = minTileY; y < maxTileY; y++)
		{
			for (int x = minTileX; x < maxTileX; x++)
			{
				currTile = tiles[y][x];
				if (currTile != nullptr)
				{
					overlappingTiles++;
				}
			}
		}

		// if more than 80% of player is buried in tiles, push them up
		if (overlappingTiles > (maxTileX - minTileX) * (maxTileY - minTileY) * 0.8)
		{
			player->position.y += player->size.y;
		}
	}

	// iterating over tiles in player's vicinity, checking for collision
	for (int y = minTileY; y < maxTileY; y++)
	{
		for (int x = minTileX; x < maxTileX; x++)
		{
			currTile = tiles[y][x];

			if (currTile != nullptr)
			{

				dx = abs(player->position.x - currTile->position.x);
				dy = abs(player->position.y - currTile->position.y);
				dxMin = (player->size.x + U_P) / 2;
				dyMin = (player->size.y + U_P) / 2;

				// true if player is intersecting tile
				if (dx < dxMin and dy < dyMin)
				{
					// distance player needs to be displaced to no longer intersect tile
					float sx = dxMin - dx;
					float sy = dyMin - dy;

					// if x correction is smaller, push player horizontally
					if (sx < sy)
					{
						// 1 = player is on right, -1 = player is on left
						int sign = (player->position.x > currTile->position.x ? 1 : -1);
						sx *= sign;

						if (tiles[y][x + sign] == nullptr)
						{
							// checks if player is approaching a one-tile high wall and steps over it
							bool canStep = currTile->position.y - U_P / 2 <= player->position.y - player->size.y / 2;

							if (canStep)
							{
								// makes sure there is room for the player above step
								for (int i = 1; i <= player->size.y / U_P; i++)
								{
									if (tiles[y + i][x] != nullptr)
									{
										canStep = false;
										break;
									}
								}
							}

							if (canStep)
							{
								player->position.y += sy;
								player->onGround = true;

								if (player->isDiving)
									initRipple();
							}
							else
							{
								player->position.x += sx;
								player->velocity.x = 0;
							}
						}
					}
					// y correction is smaller, push player vertically
					else
					{
						// 1 = player is above, -1 = player is below
						int sign = (player->position.y < currTile->position.y ? -1 : 1);
						sy *= sign;

						// check that player could have realistically contacted tile
						if (tiles[y + sign][x] == nullptr)
						{
							if (sign == 1 and player->velocity.y <= 0)
							{
								player->onGround = true;

								if (player->isDiving)
								{
									initRipple();
								}
							}

							// stop player if falling down
							if (player->velocity.y < 0)
								player->velocity.y = 0;

							player->position.y += sy;
						}
					}
				}
			}
		}
	}
}