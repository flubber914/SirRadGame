#ifndef IMAGERENDERER_H
#define IMAGERENDERER_H
#include "SDL.h"
#include <string>

class ImageRenderer
{
public:
	ImageRenderer();
	ImageRenderer(SDL_Window* window);
	~ImageRenderer();
	bool Init();
	SDL_Surface* GetSurface() { return gScreenSurface; };
	SDL_Renderer* GetRenderer() { return renderer; };
	SDL_Window* GetWindow() { return gWindow; };
	SDL_Surface* loadSurface(std::string path);
private:
	SDL_Renderer* renderer;
	SDL_Window* gWindow;
	SDL_Surface* gScreenSurface;
};
#endif