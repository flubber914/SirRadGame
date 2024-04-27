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

bool ImageRenderer::loadPixelsFromFile(std::string path)
{
    cout << path << endl;
    //Free preexisting assets
    free();

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Convert surface to display format
        mSurfacePixels = SDL_ConvertSurfaceFormat(loadedSurface, SDL_GetWindowPixelFormat(gWindow), 0);
        if (mSurfacePixels == NULL)
        {
            printf("Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            //Get image dimensions
            mWidth = mSurfacePixels->w;
            mHeight = mSurfacePixels->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return mSurfacePixels != NULL;
}
bool ImageRenderer::loadMedia(std::string path)
{
    //Loading success flag
    bool success = true;

    //Load Foo' texture pixel
    if (!loadPixelsFromFile(path))
    {
        printf("Unable to load Foo' texture!\n");
        success = false;
    }
    else
    {
        //Get pixel data
        Uint32* pixels = getPixels32();
        int pixelCount = getPitch32() * getHeight(path);

        //Map colors
        Uint32 colorKey = mapRGBA(0x00, 0x00, 0x00, 0xFF);
        Uint32 transparent = mapRGBA(0xFF, 0xFF, 0xFF, 0x00);
        //Color key pixels
        for (int i = 0; i < pixelCount; ++i)
        {
            if (pixels[i] == colorKey)
            {
                pixels[i] = transparent;
            }
        }

        //Create texture from manually color keyed pixels
        if (!loadFromPixels())
        {
            printf("Unable to load Foo' texture from surface!\n");
        }
    }

    return success;
}

Uint32 ImageRenderer::mapRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 pixel = 0;

    if (mSurfacePixels != NULL)
    {
        pixel = SDL_MapRGBA(mSurfacePixels->format, r, g, b, a);
    }

    return pixel;
}

int ImageRenderer::getWidth(std::string path)
{

    return mWidth;
}

int ImageRenderer::getHeight(std::string path)
{
    return mHeight;
}

bool ImageRenderer::loadFromPixels()
{
    //Only load if pixels exist
    if (mSurfacePixels == NULL)
    {
        printf("No pixels loaded!");
    }
    else
    {
        //Color key image
        SDL_SetColorKey(mSurfacePixels, SDL_TRUE, SDL_MapRGB(mSurfacePixels->format, 0, 0xFF, 0xFF));

        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(renderer, mSurfacePixels);
        if (mTexture == NULL)
        {
            printf("Unable to create texture from loaded pixels! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            //Get image dimensions
            mWidth = mSurfacePixels->w;
            mHeight = mSurfacePixels->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(mSurfacePixels);
        mSurfacePixels = NULL;
    }

    //Return success
    return mTexture != NULL;
}

bool ImageRenderer::loadFromFile(std::string path)
{
    //Load pixels
    if (!loadPixelsFromFile(path))
    {
        printf("Failed to load pixels for %s!\n", path.c_str());
    }
    else
    {
        //Load texture from pixels
        if (!loadFromPixels())
        {
            printf("Failed to texture from pixels from %s!\n", path.c_str());
        }
    }

    //Return success
    return mTexture != NULL;
}

Uint32* ImageRenderer::getPixels32()
{
    Uint32* pixels = NULL;

    if (mSurfacePixels != NULL)
    {
        pixels = static_cast<Uint32*>(mSurfacePixels->pixels);
    }

    return pixels;
}

Uint32 ImageRenderer::getPitch32()
{
    Uint32 pitch = 0;

    if (mSurfacePixels != NULL)
    {
        pitch = mSurfacePixels->pitch / 4;
    }

    return pitch;
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

void ImageRenderer::free()
{
    //Free texture if it exists
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }

    //Free surface if it exists
    if (mSurfacePixels != NULL)
    {
        SDL_FreeSurface(mSurfacePixels);
        mSurfacePixels = NULL;
    }
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
        SDL_SetTextureBlendMode(draw->image_Texture, SDL_BLENDMODE_BLEND);
        //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderCopyEx(renderer, draw->image_Texture, clip, &rect, draw->Rotation, NULL, draw->CharacterFlip);
    }
}

