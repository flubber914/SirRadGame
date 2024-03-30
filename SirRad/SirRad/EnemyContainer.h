#ifndef ENEMYCONTAINER_H
#define ENEMYCONTAINER_H
#include "Fireball.h"
#include <typeinfo>

class GameEngine;
class EnemyContainer
{
public:
	enum EnemyTypes { fireball };
	EnemyContainer(int _count, EnemyTypes enemyType, float _spawnDelay, float _spawnWait, GameEngine* _parent);
	~EnemyContainer();
	void ControlContained();
	void RenderContained();
	void Spawn();
private:
	void CreateEnemies(int _count, EnemyTypes enemyType);
	GameEngine* parent;
	std::vector<Enemy*> containedEnemy;
	float lastSpawn = 0;
	float spawnDelay;
	float spawnWait;
};
#endif
