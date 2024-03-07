#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H
#include <stdlib.h>
#include <iostream>
#include "SplashRectangle.h"
#include "SDL.h"
using namespace std;
class GameOfLife
{
public:
	GameOfLife();
	GameOfLife(int width, int height, SDL_Renderer* _renderer);
	~GameOfLife();
	GameOfLife& Create(int width, int height, SDL_Renderer* _renderer);
	void ScreenClick(int x, int y);
	void DrawLife();
	void DrawCharacter(Character* draw);
	void ChangeLife();
private:
	void CreateLife();
	bool GetRandomBool();
	int screenWidth; int screenHeight;
	static const int Xsize = 100;
	static const int Ysize = 100;
	bool grid[Xsize][Ysize];
	SDL_Renderer* renderer;
};
#endif
