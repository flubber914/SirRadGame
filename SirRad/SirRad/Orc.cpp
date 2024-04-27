#include "Orc.h"
#include "GameEngine.h"
#include "EnemyContainer.h"

class EnemyContainer;

Orc::Orc() : Enemy(size, position, &speed, "Images/OrcSheet.png", 3)
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
		currentAnimation = 2;
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
	int side = rand() % 2;
	size[0] = 64;
	size[1] = 64;
	position[0] = (parent->GWindow.GetWindow()->w * side) - (size[0] * side) + (size[0]/2);
	position[1] = (parent->GWindow.GetWindow()->h);
	ChangeDirection(0);
	if (side == 0) 
	{
		direction[0] = 0.2f;
	}
	else 
	{
		direction[0] = -0.2f;
	}
	direction[1] = 1;
	currentAnimation = 1;
	currentFrame = 0;
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

void Orc::ChangeDirection(int direction)
{
	if (position[0] > parent->GWindow.GetMiddleW()) 
	{
		CharacterFlip = SDL_FLIP_NONE;
	}
	else 
	{
		CharacterFlip = SDL_FLIP_HORIZONTAL;
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
