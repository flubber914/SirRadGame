#include "Orc.h"
#include "GameEngine.h"
#include "EnemyContainer.h"

class EnemyContainer;

Orc::Orc() : Enemy(size, position, &speed, "Images/Hi.png", 0)
{
	name = "Orc";
}

Orc::~Orc()
{
}

bool Orc::Move()
{
	if (position[1] > parent->GWindow.GetRampTop()) 
	{
		position[0] -= speed * direction[0];
		position[1] -= speed * direction[1];
	}
	else 
	{
		ThrowAxe();
	}
	FindCollisionZone();
	CheckBoundaries();
	parent->Collider.CheckCollision(this);
	return false;
}

void Orc::Death()
{
	isSpawned = false;
}

void Orc::Spawn()
{
	speed = 1;
	AxeContainer = parent->enemyContainers[4];
	cout << parent->enemyContainers.size() << endl;
	int side = rand() % 2;
	size[0] = 64;
	size[1] = 64;
	position[0] = (parent->GWindow.GetWindow()->w * side) - (size[0] * side);
	position[1] = (parent->GWindow.GetWindow()->h);
	if (side == 0) 
	{
		direction[0] = 0.2f;
	}
	else 
	{
		direction[0] = -0.2f;
	}
	direction[1] = 1;
	isSpawned = true;
}

void Orc::Collide(Character* other)
{
	if (other->name == "SirRad")
	{
		cout << "Orcy!" << endl;
		Death();
	}
}

void Orc::ThrowAxe()
{
	if (parent->totalTime - lastThrown > throwSpeed) 
	{
		cout << "throw" << endl;
		throwing = true;
		lastThrown = parent->totalTime;
		AxeContainer->Spawn();
		throwing = false;
	}
}
