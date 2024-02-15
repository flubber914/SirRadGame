#ifndef aTimerFILE
#define aTimerFILE
#include <iostream>
#include <SDL.h>
// written by oszymanezyk@lincoln.ac.uk
// part of games programming module
class SZ_Timer
{
private:
	int startTicks; // SDL time when the timer started
public:
	SZ_Timer();
	//SDL timer stuff
	void resetTicksTimer(); // resets timer to zero
	int getTicks(); // returns how much time has passed since timer has been reset
};
#endif