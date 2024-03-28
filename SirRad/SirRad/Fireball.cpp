#include "Fireball.h"
#include "GameEngine.h"

Fireball::Fireball() : Enemy(size, position, &speed, "Images/Hi.png", 0)
{
}

Fireball::~Fireball()
{
}

bool Fireball::Move()
{
	position[0] += speed * direction[0];
	position[1] -= speed * direction[1];
	FindCollisionZone();
	parent->Collider.CheckCollision(this);
	return false;
}

void Fireball::Death()
{
}

void Fireball::Spawn()
{
	speed = 5;
	int side = rand() % 2;
	position[0] = (parent->GWindow.GetWindow()->w * side) - (size[0] * side);
	position[1] = (rand() % parent->GWindow.GetWindow()->h);
	size[0] = 32;
	size[1] = 32;
	direction.push_back(-((float)position[0] - (float)parent->SirRad.GetPosX())/ (float)parent->GWindow.GetWindow()->w);
	direction.push_back(((float)position[1] - (float)parent->SirRad.GetPosY()) / (float)parent->GWindow.GetWindow()->h);
	isSpawned = true;
}

void Fireball::Attack()
{
}

void Fireball::Damage()
{
}

void Fireball::Collide(Character other)
{
	cout << "bang!" << endl;
}
