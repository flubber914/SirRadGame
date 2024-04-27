#include "SZ_Timer.h"
#include "GameEngine.h"
SZ_Timer::SZ_Timer()
{
}
SZ_Timer::SZ_Timer(GameEngine* _parent)
{
	parent = _parent;
	parent->PrintLog("SZ_Timer was created, thanks Oliver!");
	startTicks = 0;
}
SZ_Timer::~SZ_Timer()
{
	parent->PrintLog("SZ_Timer Unloaded");
}
;
void SZ_Timer::resetTicksTimer()
{
	startTicks = SDL_GetTicks(); // numbers of milliseconds since start of SDL program
	//printf("timer started! %i \n", startTicks);
}
int SZ_Timer::getTicks()
{
	//printf("getTicks! %i \n", SDL_GetTicks() - startTicks);
	return (SDL_GetTicks() - startTicks); //Return the current time minus the start time
}