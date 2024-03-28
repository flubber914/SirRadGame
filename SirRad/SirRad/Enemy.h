#ifndef ENEMY_H
#define ENEMY_H
#include "Character.h"
class Enemy :
    public Character
{
public:
    Enemy(int _size[2], int _position[2], int* _speed, string _ImagePath, int _spriteRows);
    ~Enemy();
    virtual void Death();
    virtual void Spawn();
    virtual void Attack();
    virtual void Damage();
    bool GetSpawned() { return isSpawned; };
protected:
    bool isSpawned = false;
};
#endif

