#ifndef CHARACTER_H
#define CHARACTER_H

using namespace std;

#include <vector>

class Character
{
public:
	Character();//default Constructor
	Character(int _size[2], int _position[2], int* _speed);
	virtual ~Character();
	virtual bool Move(bool moveRight);
	int GetSizeW() { return size[0]; }
	int GetSizeH() { return size[1]; }
	int GetPosX() { return position[0]; }
	int GetPosY() { return position[1]; }

protected:
	int size [2]; //two numbers relating to the size w,h
	int position [2]; //two numbers relating to position x,y
	int speed; //player movement
};
#endif
