#include "SplashRectangle.h"

SplashRectangle::SplashRectangle()
{
}

SplashRectangle::SplashRectangle(int _size[2], int _position[2], int* _speed) : Character(_size, _position, _speed, "None")
{
}

SplashRectangle::~SplashRectangle()
{
}

bool SplashRectangle::Move(bool moveRight)
{
	if (moveRight) {
		position[0] += speed;
	}
	else {
		position[0] -= speed;
	}
	return false;
}

void SplashRectangle::SetPosition(int _position[2])
{
	position[0] = _position[0];
	position[1] = _position[1];
}

void SplashRectangle::SetSize(int _size[2])
{
	size[0] = _size[0];
	size[1] = _size[1];
}
