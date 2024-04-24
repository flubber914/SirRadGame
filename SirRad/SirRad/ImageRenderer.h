#ifndef IMAGERENDERER_H
#define IMAGERENDERER_H
#include "SDL.h"
#include <string>
#include "Character.h"

class ImageRenderer
{
public:
	ImageRenderer(SDL_Window* window);
	~ImageRenderer();
	bool Init();
	SDL_Surface* GetSurface() { return gScreenSurface; };
	SDL_Renderer* GetRenderer() { return renderer; };
	SDL_Window* GetWindow() { return gWindow; };
	SDL_Surface* loadSurface(std::string path);
	void DrawCharacter(Character* draw, SDL_Rect* clip = NULL);
	void DrawText();
private:
	SDL_Renderer* renderer;
	SDL_Window* gWindow;
	SDL_Surface* gScreenSurface;
};
#endif
//reference https://lazyfoo.net/tutorials/SDL/11_clip_rendering_and_sprite_sheets/index.php