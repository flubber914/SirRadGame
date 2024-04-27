#include "GameWindow.h"
#include "GameEngine.h"

GameWindow::GameWindow()
{
}

GameWindow::GameWindow(SDL_Surface* window, GameEngine* _parent)
{
	parent = _parent;
	parent->PrintLog("Window stats calculated for functions");
	gWindow = window;
	Screen_MiddleW = window->w / 2;
	Screen_MiddleH = window->h / 2;
	Screen_EighthW = window->w / 8;
	Screen_EighthH = window->h / 8;
	Game_Floor = window->h - Screen_EighthH;
	rampTop = Game_Floor - (window->h/3);
}

GameWindow::~GameWindow()
{
	parent->PrintLog("GameWindow Unloaded");
}
