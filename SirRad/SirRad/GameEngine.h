#ifndef GameEngine_H
#define GameEngine_H

#include <stdio.h>
#include <cstdlib>
#include <iostream>

#include "SDL.h"
#include "Player.h"
#include "SplashRectangle.h"
#include "SZ_Timer.h"

class GameEngine
{
public:
	GameEngine(SDL_Window* window); ///constructor
	~GameEngine(); //destructor
private:
	SZ_Timer aTimer;
	Player SirRad;
	bool quit = false;
	SDL_Renderer* renderer;
	SDL_Event event;
	SDL_Surface* screenSurface;
	void GameLoop(); //the main game loop
	void Update(); //updates values of objects
	void Render(); //renders updated objects 
	void DrawCharacter(Character* draw); //Draws all characters for the renderer

	//splash screen
	int splashFrames = 300;
	void Splash();
};
#endif

