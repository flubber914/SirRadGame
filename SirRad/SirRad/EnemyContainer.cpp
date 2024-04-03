#include "EnemyContainer.h"
#include "GameEngine.h"
#include "Fireball.h"
#include "Orc.h"
#include "Axe.h"

EnemyContainer::EnemyContainer(int _count, EnemyTypes enemyType, float _spawnDelay, float _spawnWait, GameEngine* _parent)
{
	parent = _parent;
	parent->enemyContainers.push_back(this);
	CreateEnemies(_count, enemyType);
	spawnDelay = _spawnDelay * 1000;
	spawnWait = _spawnWait * 1000;
}

EnemyContainer::~EnemyContainer()
{
	int length = containedEnemy.size();
	for (int i = 0; i < length; i++)
	{
		delete containedEnemy[0];
	}
}

void EnemyContainer::ControlContained()
{
	for (int i = 0; i < containedEnemy.size(); i++)
	{
		if (containedEnemy[i]->GetSpawned()) {
			containedEnemy[i]->Move();
		}
	}
}

void EnemyContainer::RenderContained()
{
	for (int i = 0; i < containedEnemy.size(); i++)
	{
		if (containedEnemy[i]->GetSpawned()) {
			parent->ImageRender.DrawCharacter(containedEnemy[i]);
		}
	}
}

void EnemyContainer::Spawn()
{
	if ((parent->totalTime > spawnDelay) && ((parent->totalTime - lastSpawn) > spawnWait) || spawnWait == -1000) 
	{
		for (int i = 0; i < containedEnemy.size(); i++)
		{
			if (!containedEnemy[i]->GetSpawned())
			{
				containedEnemy[i]->Spawn();
				lastSpawn = parent->totalTime;
				break;
			}
		}
	}
}

void EnemyContainer::CreateEnemies(int _count, EnemyTypes enemyType)
{
	for (int i = 0; i < _count; i++)
	{
		Enemy* newEnemy{};
		switch (enemyType)
		{
		case fireball:
			newEnemy =  new Fireball();
			break;
		case orc:
			newEnemy = new Orc();
			break;
		case axe:
			newEnemy = new Axe();
			break;
		default:
			cout << "ERROR: not an enemy type" << endl;
			break;
		}
		newEnemy->Init(parent);
		containedEnemy.push_back(newEnemy);
	}
}
