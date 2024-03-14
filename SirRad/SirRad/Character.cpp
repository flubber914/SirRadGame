#include "Character.h"
#include "GameEngine.h"

Character::Character()
{
	size[0] = 10; size[1] = 10;
	position[0] = 10; position[1] = 10;
	speed = 2;
}
/// <summary>
/// this constructor sets character statistics
/// </summary>
Character::Character(int _size [2], int _position [2], int* _speed, string _ImagePath)
{
	size[0] = _size[0]; size[1] = _size[1];
	position[0] = _position[0]; position[1] = _position[1];
	speed = *_speed;
	ImagePath = _ImagePath;
	character_Surface = SDL_CreateRGBSurface(0, GetSizeW(), GetSizeH(), 32, 0, 0, 0, 0);

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

void Character::Init(GameEngine* _parent)
{
	parent = _parent;
	if (ImagePath != "None") {
		image_Texture = SDL_CreateTextureFromSurface(parent->ImageRender.GetRenderer(), parent->ImageRender.loadSurface(ImagePath));
	}
}

void Character::ChangeDirection(int _direction)
{
}
