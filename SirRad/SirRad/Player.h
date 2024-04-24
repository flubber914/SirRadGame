#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include "Vector2D.h"
class Player :
    public Character
{
public:
    Player();//default Constructor
    Player(int _size [2], int _position[2], int* _speed, string _ImagePath);
    ~Player();
    bool Move() override;
    void Movement(bool moveLeft, bool moveRight);
    void ChangeDirection(int _direction) override;
    void ChangeMoveZone(int newZone);
    void Collide(Character* other) override;
    void SetRotation();
    void Animate() override;
    void DoTrick(int type);
    Vector2D velocity;
    bool performingTrick = false;
    int trickType = 0;
private:
    int MoveZone;
    int EntrySpeed;
};
#endif

