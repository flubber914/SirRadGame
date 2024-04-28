#ifndef SPLASHRECTANGLE_H
#define SPLASHRECTANGLE_H
#include "Character.h"
class GameEngine;

class SplashRectangle :
    public Character
{
public:
    SplashRectangle();
    SplashRectangle(int _size[2], int _position[2], int* _speed, string ImagePath);
    ~SplashRectangle();
    bool Move() override;
    void SetPosition(int _position[2]);
    void SetSize(int _size[2]);
    string name = "box";
private:
};
#endif // !SPLASHRECTANGLE_H
