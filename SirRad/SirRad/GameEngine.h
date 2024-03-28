#ifndef GameEngine_H
#define GameEngine_H

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <list>
#include <string>

#include "SDL.h"
#include "Player.h"
#include "Fireball.h"
#include "ImageRenderer.h"
#include "SoundPlayer.h"
#include "SplashRectangle.h"
#include "SZ_Timer.h"
#include "GameOfLife.h"
#include "ColourGame.h"
#include <SDL_image.h>
#include <SDL_audio.h>
#include "GameWindow.h"
#include "Character.h"

class GameEngine
{
public:
	GameEngine(SDL_Window* window); ///constructor
	~GameEngine(); //destructor
	SDL_Surface* screenSurface;
	GameWindow GWindow;
	ImageRenderer ImageRender;
	SoundPlayer SoundPlayer;
	Player SirRad;
	Fireball works;
private:
	SZ_Timer aTimer;
	bool quit = false;
	bool leftMousePressed = false;
	int count = 0;
	//SDL_Renderer* renderer;
	SDL_Event event;
	//GameOfLife *Life;
	ColourGame *game;
	void GameLoop(); //the main game loop
	void Input();
	void Update(); //updates values of objects
	void Render(); //renders updated objects 
	//void DrawCharacter(Character* draw); //Draws all characters for the renderer

	////////////Movement Variables
	bool MoveLeft = false;
	bool MoveRight = false;

	//splash screen
	int splashFrames = 300;
	void Splash();
};
#endif

