#include "Player.h"

Player::Player()
{
}

Player::Player(int _size[2], int _position[2], int* _speed) : Character(_size, _position, _speed)
{
}

Player::~Player()
{
}
/// <summary>
/// The player moves from left to right taking into account it's x value to determine it's direction and rotation
/// </summary>
/// <param name="moveRight">whether the characters input direction is right or not</param>
/// <returns>whether the character was able to move</returns>
bool Player::Move(bool moveRight)
{
	if (moveRight) 
	{
		position[0] += speed;
	}
	else 
	{
		position[0]-= speed;
	}
	return false;
}
