#include "ImageRenderer.h"
#include "GameEngine.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

ImageRenderer::ImageRenderer(SDL_Window* window, GameEngine* _parent)
{
    parent = _parent;
    parent->PrintLog("renderer created");
    gWindow = window;
    renderer = SDL_CreateRenderer(gWindow, -1, 0);

    Init();
}

ImageRenderer::~ImageRenderer()
{
    parent->PrintLog("renderer Unloaded");
}

bool ImageRenderer::Init()
{
    //Initialization flag
    bool success = true;
    string error;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        error = SDL_GetError();
        parent->PrintLog("SDL could not initialize Renderer! SDL Error: " + error);
        success = false;
    }
    else
    {
        //Create window
        if (gWindow == NULL)
        {
            error = SDL_GetError();
            parent->PrintLog("Window was not created! SDL Error: " + error);
            success = false;
        }
        else
        {
            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                error = IMG_GetError();
                parent->PrintLog("SDL_image could not initialize! SDL_image Error: " + error);
                success = false;
            }
            else
            {
                //Get window surface
                parent->PrintLog("SDL_image was initialized! \n");
                gScreenSurface = SDL_GetWindowSurface(gWindow);
            }
        }
    }
    parent->PrintLog("renderer initialisation was successful: " + to_string(success));

    return success;
}


SDL_Surface* ImageRenderer::loadSurface(string path)
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    SDL_BlitSurface(loadedSurface, NULL, loadedSurface, NULL);
    if (loadedSurface == NULL)
    {
        parent->PrintLog("Unable to load image %s! SDL_image Error: %s\n" + path + IMG_GetError());
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
        if (optimizedSurface == NULL)
        {
            parent->PrintLog("Unable to optimize image %s! SDL Error: " + path + SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    parent->PrintLog("surface " + path + " was loaded");

    return optimizedSurface;
}

void ImageRenderer::DrawCharacter(Character* draw, SDL_Rect* clip)
{
    SDL_Rect rect = { draw->GetPosX() - (draw->GetSizeW() / 2), draw->GetPosY() - (draw->GetSizeH() / 2), draw->GetSizeW(), draw->GetSizeH() };
    //SDL_RenderFillRect(renderer, &rect);
    //SDL_RenderDrawRect(renderer, &rect);
    if (draw->GetImagePath() != "None") {
        SDL_Point window_position = {         //    Position of window
            draw->GetPosX(),
            draw->GetPosY()
        };
        if (clip != NULL) 
        {
            rect.w = clip->w;
            rect.h = clip->h;
        }
        //SDL_SetTextureBlendMode(draw->image_Texture, SDL_BLENDMODE_BLEND);
        //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderCopyEx(renderer, draw->image_Texture, clip, &rect, draw->Rotation, NULL, draw->CharacterFlip);
    }
}

