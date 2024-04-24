#include "Fireball.h"
#include "GameEngine.h"

Fireball::Fireball() : Enemy(size, position, &speed, "Images/Hi.png", 0)
{
	name = "Fireball";
}

Fireball::~Fireball()
{
}

bool Fireball::Move()
{
	position[0] -= speed * direction[0];
	position[1] -= speed * direction[1];
	FindCollisionZone();
	CheckBoundaries();
	parent->Collider.CheckCollision(this);
	return false;
}

void Fireball::Death()
{
	isSpawned = false;
}

void Fireball::Spawn()
{
	speed = 5;
	int side = rand() % 2;
	size[0] = 32;
	size[1] = 32;
	position[0] = (parent->GWindow.GetWindow()->w * side) - (size[0] * side);
	position[1] = (rand() % parent->GWindow.GetWindow()->h);
	direction[0] = (((float)position[0] - (float)parent->SirRad.GetPosX()) / (float)parent->GWindow.GetWindow()->w);
	direction[1] = (((float)position[1] - (float)parent->SirRad.GetPosY()) / (float)parent->GWindow.GetWindow()->h);
	isSpawned = true;
	hit = false;
}

void Fireball::Attack()
{
}

void Fireball::Damage()
{
}

void Fireball::Collide(Character* other)
{
	cout << other->name << endl;
	if (other->name == "SirRad" && !hit) {
		hit = true;
		if (parent->SirRad.performingTrick)
		{
			cout << "dodged with trick" << endl;
			parent->ChangeScore(500);
		}
		else
		{
			cout << "Fireball Hit!" << endl;
			parent->ChangeScore(-300);
			Death();
		}
	}
}
