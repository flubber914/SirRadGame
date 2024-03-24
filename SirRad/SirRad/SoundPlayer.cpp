#include "SoundPlayer.h"
#include "GameEngine.h"

SoundPlayer::SoundPlayer() 
{
	Init();
}

SoundPlayer::~SoundPlayer()
{
}

Mix_Music* SoundPlayer::MixMusic(std::string location)
{
    bool success = true;
    Mix_Music* loadSound = Mix_LoadMUS(location.c_str());
    if (loadSound == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    return loadSound;
}

void SoundPlayer::Init()
{
	bool success = true;
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize SoundPlayer! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Initialize SDL_mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
            success = false;
        }
    }
}
//reference https://lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php#:~:text=To%20initialize%20SDL_mixer%20we%20need,we're%20using%20the%20default.
