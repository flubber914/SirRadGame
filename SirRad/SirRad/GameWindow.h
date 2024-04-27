#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include "SDL.h"
#include <string>
class GameEngine;

class GameWindow
{
public:
	GameWindow();
	GameWindow(SDL_Surface* window, GameEngine* parent);
	~GameWindow();
	SDL_Surface* GetWindow() { return gWindow; };
	int GetMiddleW() { return Screen_MiddleW; };
	int GetMiddleH() { return Screen_MiddleH; };
	int GetEighthW() { return Screen_EighthW; };
	int GetEighthH() { return Screen_EighthH; };
	int GetFloor() { return Game_Floor; };
	int GetRampTop() { return rampTop; };
private:
	SDL_Surface* gWindow;
	int Screen_MiddleW;
	int Screen_MiddleH;
	int Screen_EighthW;
	int Screen_EighthH;
	int Game_Floor;
	int rampTop;
	GameEngine* parent;
};
#endif
