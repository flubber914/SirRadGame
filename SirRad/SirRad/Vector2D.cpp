#include "Vector2D.h"

Vector2D::Vector2D()
{
}

Vector2D::Vector2D(int eX, int eY)
{
}

float Vector2D::magnitude()
{
	return sqrt(pow(X, 2) + pow(Y, 2));
}
