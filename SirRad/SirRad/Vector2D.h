#ifndef VECTOR2D_H
#define VECTOR2d_H
#include <cmath>
class Vector2D
{
public:
	Vector2D();
	Vector2D(int eX, int eY);
	int X, Y;
	float magnitude();
};
#endif

