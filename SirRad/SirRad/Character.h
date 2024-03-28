#ifndef CHARACTER_H
#define CHARACTER_H

using namespace std;

#include <vector>
#include <string>
#include <SDL_image.h>

class GameEngine;

class Character
{
public:
	Character();//default Constructor
	Character(int _size[2], int _position[2], int* _speed, string _ImagePath, int _spriteRows = NULL);
	virtual ~Character();
	virtual bool Move(bool moveRight);
	int GetSizeW() { return size[0]; }
	int GetSizeH() { return size[1]; }
	int GetPosX() { return position[0]; }
	int GetPosY() { return position[1]; }
	SDL_Surface* GetSurface() { return character_Surface; }
	void Init(GameEngine* _parent);
	string GetImagePath() { return ImagePath; }
	GameEngine* parent;
	SDL_Surface* character_Surface;
	SDL_Texture* image_Texture;
	virtual void ChangeDirection(int _direction);


	///FOR SPRITES
	int spriteRows = 1;
	int CurrentSpriteClip = 0;
	vector<SDL_Rect> SpriteClips;
	void LoadSprites();

protected:
	int size [2]; //two numbers relating to the size w,h
	int position [2]; //two numbers relating to position x,y
	int speed; //player movement
	float speedUp;
	vector<float> direction;
	string ImagePath;

};
#endif
