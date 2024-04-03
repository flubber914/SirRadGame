#include "Axe.h"
#include "GameEngine.h"
#include "EnemyContainer.h"

Axe::Axe() : Enemy(size, position, &speed, "Images/Hi.png", 0)
{
	name = "Axe";
}

Axe::~Axe()
{
}

bool Axe::Move()
{
	position[0] -= direction[0] * speed;
	position[1] -= direction[1] * speed;
	direction[1] -= 0.05f;
	FindCollisionZone();
	CheckBoundaries();
	parent->Collider.CheckCollision(this);
	return false;
}

void Axe::Death()
{
	cout << "aaaaah! I'm an axe" << endl;
	isSpawned = false;
}

void Axe::Spawn()
{
	speed = 1;
	OrcContainer = parent->enemyContainers[2];
	for (int i = 0; i < OrcContainer->GetContainedEnemy().size(); i++)
	{
		if (OrcContainer->GetContainedEnemy()[i]->GetThrowing())
		{
			size[0] = 32;
			size[1] = 32;
			position[0] = OrcContainer->GetContainedEnemy()[i]->GetPosX();
			position[1] = OrcContainer->GetContainedEnemy()[i]->GetPosY();
			if (OrcContainer->GetContainedEnemy()[i]->GetDirection()[0] > 0)
			{
				direction[0] = -1;
			}
			else 
			{
				direction[0] = 1;
			}
			direction[1] = 3;
			axeHit = false;
			isSpawned = true;
			break;
		}
	}
}

void Axe::Collide(Character* other)
{
	if (!axeHit) 
	{
		if (other->name == "SirRad")
		{
			axeHit = true;
			cout << "The axe is lit" << endl;
		}
	}
}
