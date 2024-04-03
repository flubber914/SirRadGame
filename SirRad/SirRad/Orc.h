#ifndef ORC_H
#define ORC_H
#include "Enemy.h"

class EnemyContainer;

class Orc :
    public Enemy
{
public:
    Orc();
    ~Orc();
    bool Move() override;
    void Death() override;
    void Spawn() override;
    void Collide(Character* other) override;
private:
    void ThrowAxe();
    float lastThrown = 0;
    float throwSpeed = 2000;
    EnemyContainer* AxeContainer;
};
#endif