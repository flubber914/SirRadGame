#ifndef COLOURGAME_H
#define COLOURGAME_H
#include <chrono>
#include "SDL.h"
#include "SZ_Timer.h"
#include "SplashRectangle.h"
class ColourGame
{
public:
	ColourGame();
	ColourGame(SDL_Renderer* _renderer);
	~ColourGame();
	ColourGame& Create(SDL_Renderer* _renderer);
	void StartGame();
	bool NextColour();
	enum colour { Red, Orange, Yellow, Green, Blue, White, Count };
	void SetColour(colour colour);
	void RecieveInput(colour answer);
	colour GenerateNewColour();
	colour GetAnswer();
	colour GetQuestion();
	SplashRectangle rect;
	int length = 0;
	int duration = 15;
private:
	colour question;
	colour answer;
	SDL_Renderer* renderer;
	SZ_Timer aTimer;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	int score;
};

#endif