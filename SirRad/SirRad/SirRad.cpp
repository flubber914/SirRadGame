// SirRad!.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SDL.h"
#include "GameEngine.h"

int main(int argc, char* argv[])
{
    srand(time(0));
    bool exit = false;
    //Try to initialise.. if we can't, then exit this program:
    //if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        //  return 1;
    //Create a window
    SDL_Window* window = SDL_CreateWindow("Sir Rad!", 100, 100, 800, 400, SDL_WINDOW_SHOWN);

    GameEngine theGame = GameEngine(window);
    //Finally, exit
    return 0;
}