#include "Enemy.h"

Enemy::Enemy(int _size[2], int _position[2], int* _speed, string _ImagePath, int _spriteRows) : Character(_size, _position, _speed, _ImagePath, _spriteRows)
{

}

Enemy::~Enemy()
{
}

void Enemy::Death()
{
}

void Enemy::Spawn()
{
}

void Enemy::Attack()
{
}

void Enemy::Damage()
{
}

bool Enemy::DetectCollision()
{

	return false;
}
