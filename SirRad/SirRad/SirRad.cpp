// SirRad!.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SDL.h"
#include "GameEngine.h"

int main(int argc, char* argv[])
{
    srand(time(NULL));
    bool exit = false;
    //Try to initialise.. if we can't, then exit this program:
    //if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        //  return 1;
    //Create a window
    SDL_Window* window = SDL_CreateWindow("16598945 - Sir Rad!", 100, 100, 800, 450, 4);


    GameEngine theGame = GameEngine(window);
    //Finally, exit and unload everything
    SDL_Quit();
    return 0;
}