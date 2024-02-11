#include "Character.h"

Character::Character()
{
	size[0] = 10; size[1] = 10;
	position[0] = 10; position[1] = 10;
	speed = 2;
}
/// <summary>
/// this constructor sets character statistics
/// </summary>
Character::Character(int _size [2], int _position [2], int* _speed)
{
	size[0] = _size[0]; size[1] = _size[1];
	position[0] = _position[0]; position[1] = _position[1];
	speed = *_speed;
}
/// <summary>
/// this virtual constructor for the virtual class Character
/// </summary>
Character::~Character()
{
}
/// <summary>
/// This virual Function is the basis of all movement of all characters in the game
/// </summary>
/// <returns></returns>
bool Character::Move(bool moveRight)
{
	return false;
}
