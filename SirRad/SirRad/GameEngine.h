#ifndef GameEngine_H
#define GameEngine_H

#include <stdio.h>
#include <cstdlib>
#include <iostream>

#include "SDL.h"
#include "Player.h"
#include "SplashRectangle.h"
#include "SZ_Timer.h"
#include "GameOfLife.h"
#include "ColourGame.h"
#include <SDL_image.h>

class GameEngine
{
public:
	GameEngine();
	GameEngine(SDL_Window* window); ///constructor
	~GameEngine(); //destructor
	void DrawCharacter(Character* draw); //Draws all characters for the renderer
	SDL_Surface* screenSurface;
private:
	SZ_Timer aTimer;
	Player SirRad;
	bool quit = false;
	bool leftMousePressed = false;
	int count = 0;
	SDL_Renderer* renderer;
	SDL_Event event;
	//GameOfLife *Life;
	ColourGame *game;
	void GameLoop(); //the main game loop
	void Update(); //updates values of objects
	void Render(); //renders updated objects 
	//void DrawCharacter(Character* draw); //Draws all characters for the renderer

	//splash screen
	int splashFrames = 300;
	void Splash();
};
#endif

