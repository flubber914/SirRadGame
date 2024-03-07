#include "SZ_Timer.h"
SZ_Timer::SZ_Timer()
{
	startTicks = 0;
};
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