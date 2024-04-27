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
	bool loadPixelsFromFile(std::string path);
	bool loadFromPixels();
	bool loadFromFile(std::string path);
	bool loadMedia(std::string path);
	Uint32* getPixels32();
	Uint32 getPitch32();
	Uint32 mapRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	int getWidth(std::string path);
	int getHeight(std::string path);
	void free();
private:
	SDL_Renderer* renderer;
	SDL_Window* gWindow;
	SDL_Surface* gScreenSurface;
	SDL_Surface* mSurfacePixels;
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};
#endif
//reference https://lazyfoo.net/tutorials/SDL/11_clip_rendering_and_sprite_sheets/index.php