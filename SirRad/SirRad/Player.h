#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
class Player :
    public Character
{
public:
    Player();//default Constructor
    Player(int _size [2], int _position[2], int* _speed, string _ImagePath);
    ~Player();
    bool Move(bool moveRight) override;
private:
};
#endif

