#include "ImageRenderer.h"
#include "GameEngine.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

ImageRenderer::ImageRenderer(SDL_Window* window)
{
    printf("hi\n");
    gWindow = window;
    renderer = SDL_CreateRenderer(gWindow, -1, 0);

    Init();
}

ImageRenderer::~ImageRenderer()
{
}

bool ImageRenderer::Init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize Renderer! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        if (gWindow == NULL)
        {
            printf("Window was not created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            }
            else
            {
                //Get window surface
                printf("SDL_image was initialized! \n");
                gScreenSurface = SDL_GetWindowSurface(gWindow);
                cout << "hi" << endl;
            }
        }
    }

    return success;
}

SDL_Surface* ImageRenderer::loadSurface(string path)
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
        if (optimizedSurface == NULL)
        {
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

void ImageRenderer::DrawCharacter(Character* draw, SDL_Rect* clip)
{
    SDL_Rect rect = { draw->GetPosX() - (draw->GetSizeW() / 2), draw->GetPosY() - (draw->GetSizeH() / 2), draw->GetSizeW(), draw->GetSizeH() };
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);
    if (draw->GetImagePath() != "None") {
        if (clip != NULL) 
        {
            rect.w = clip->w;
            rect.h = clip->h;
        }
        SDL_RenderCopy(renderer, draw->image_Texture, clip, &rect);
    }
}

