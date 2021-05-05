#ifndef CONSTANTS_H
#define CONSTANTS_H

const static float U_P = 8;
const static int WIN_TILES_X = 100, WIN_TILES_Y = 75;
const static sf::Vector2f WIN_SIZE { U_P * WIN_TILES_X, U_P* WIN_TILES_Y };
const static float FRAME_DURATION = 1 / 60.f,
				   UPDATE_DURATION = 1 / 60.f,
				   GRAV_CHECK_DURATION = 1 / 25.f;
const static sf::Keyboard::Key JUMP_KEY = sf::Keyboard::W,
							   MOVE_LEFT_KEY = sf::Keyboard::A,
							   MOVE_RIGHT_KEY = sf::Keyboard::D,
							   DIVE_KEY = sf::Keyboard::S;

// PLAYER CONSTS

// speeds in x per second
const float MAX_HORIZONTAL_SPEED = 32 * U_P,
			MAX_FALL_SPEED = 64 * U_P,
			T_TO_MAX_SPEED = 0.15,
			HORIZONTAL_ACCEL = MAX_HORIZONTAL_SPEED / T_TO_MAX_SPEED,
			JUMP_VEL = 32 * U_P,
			G = 64 * U_P;
const int DIVE_COEFF = 2;

const float GROUND_JUMP_COEFF = 1.5;
const int GROUND_JUMP_COL_HEIGHT = 8;
const int RIPPLE_RADIUS = 16;
const int RIPPLE_THICKNESS = 4;
const int RAISE_BOULDER_SIZE = 5;
const float PUSH_VELOCITY = 20;

#endif