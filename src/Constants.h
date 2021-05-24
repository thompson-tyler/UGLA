#ifndef CONSTANTS_H
#define CONSTANTS_H

const static float U_P = 8.f;
const static int TILES_X = 200, TILES_Y = 150;
const static sf::Vector2f WORLD_SIZE { TILES_X * U_P, TILES_Y* U_P };
const static sf::Vector2f WIN_SIZE { 1200.f, 800.f };
const static float FRAME_DURATION = 1 / 60.f,
				   UPDATE_DURATION = 1 / 60.f,
				   GRAV_CHECK_DURATION = 1 / 30.f;
const static sf::Keyboard::Key JUMP_KEY = sf::Keyboard::W,
							   MOVE_LEFT_KEY = sf::Keyboard::A,
							   MOVE_RIGHT_KEY = sf::Keyboard::D,
							   DIVE_KEY = sf::Keyboard::S,
							   GROUND_JUMP_KEY = sf::Keyboard::Space,
							   RAISE_GROUND_KEY = sf::Keyboard::Up,
							   PUSH_GROUND_LEFT_KEY = sf::Keyboard::Left,
							   PUSH_GROUND_RIGHT_KEY = sf::Keyboard::Right,
							   ZOOM_OUT_KEY = sf::Keyboard::Hyphen,
							   ZOOM_IN_KEY = sf::Keyboard::Equal,
							   EXIT_KEY = sf::Keyboard::Escape;
const static float HEALTH_BAR_WIDTH = 50.f;

// PLAYER CONSTS

// speeds in x per second
const sf::Vector2f PLAYER_SPRITE_SHEET_SIZE = { 32, 32 };
const sf::Vector2f PLAYER_SPRITE_SIZE = { 32, 32 };
const sf::Vector2f PLAYER_HITBOX_SIZE = { 20, 30 };
const float MAX_HORIZONTAL_SPEED = 32.f * U_P,
			MAX_FALL_SPEED = 64.f * U_P,
			T_TO_MAX_SPEED = 0.15f,
			HORIZONTAL_ACCEL = MAX_HORIZONTAL_SPEED / T_TO_MAX_SPEED,
			JUMP_VEL = 32.f * U_P,
			G = 64.f * U_P;
const int DIVE_COEFF = 2;

const float GROUND_JUMP_COEFF = 1.5f;
const int GROUND_JUMP_COL_HEIGHT = 8;
const int RIPPLE_RADIUS = 16;
const int RIPPLE_THICKNESS = 8;
const int RAISE_BOULDER_SIZE = 5;
const float PUSH_VELOCITY = 20.f;

// COLORS
const sf::Color BACKGROUND_COLOR = sf::Color(244, 233, 205),
				PLAYER_COLOR = sf::Color(151, 77, 65),
				STONE_COLOR = sf::Color(75, 78, 75),
				SAND_COLOR = sf::Color(218, 181, 107),
				WATER_COLOR = sf::Color(74, 136, 217, 50);

#endif