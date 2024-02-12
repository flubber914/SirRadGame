#include "GameEngine.h"
#include <list>

/// <summary>
/// this constructor starts the game and it's loop
/// </summary>
GameEngine::GameEngine(SDL_Window* window)
{
    renderer = SDL_CreateRenderer(window, -1, 0);
    screenSurface = SDL_GetWindowSurface(window);
    int speed = 10;
    int size[2] = { 100, 100 }; int pos[2] = { 100, 100 };
    //////////////Create Starting Objects
    SirRad = Player(size, pos, &speed);
    //////////////
    Splash(); //do the splash screen at the start of the game
    GameLoop(); ////always goes last probably
}

GameEngine::~GameEngine()
{
}

void GameEngine::GameLoop()
{
    while (!quit)
    {
        Render();
        Update();
        //Handle events on queue

        //Clear screen
        //SDL_RenderClear(gRenderer);

        //Render texture to screen
        //SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

        //Update screen
        //SDL_RenderPresent(gRenderer);
        SDL_Delay(100);
    }
}
/// <summary>
/// the update of all values within the game
/// </summary>
void GameEngine::Update()
{
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            SDL_Quit();
            quit = true;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                SDL_Quit();
                quit = true;
                break;
            case SDLK_a:
                SirRad.Move(false);
                printf("eyy");
                break;
            case SDLK_d:
                SirRad.Move(true);
            default:
                break;
            }
            break;
        default:
            printf("event polled");
            break;
        }
    }
}
/// <summary>
/// the drawing of all objects within the game
/// </summary>
void GameEngine::Render()
{
    /////////////////////////draw background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    ///////////////////////// 
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    DrawCharacter(&SirRad);///////////DrawPlayer
    SDL_RenderPresent(renderer);
}

void GameEngine::DrawCharacter(Character* draw)
{
    SDL_Rect rect = { draw->GetPosX(), draw->GetPosY(), draw->GetSizeW(), draw->GetSizeH() };

    SDL_RenderFillRect(renderer, &rect);
    //SDL_RenderDrawRect(renderer, &rect);

    //SDL_RenderDrawRect(renderer, &rect);
}

void GameEngine::Splash()
{
    Uint64 start;
    Uint64 end;
    int xpos = 0 - (screenSurface->w*5);
    int ypos = 0;
    int rectangles = 6;
    bool right = true;
    list<SplashRectangle> splashArray;
    for (size_t i = 0; i < rectangles; i++)
    {
        int speed = ((screenSurface->w)) / (splashFrames/(screenSurface->w/100));
        cout << "speed" << screenSurface->w << endl;
        int size[2] = { (screenSurface->w*5), (screenSurface->h / rectangles) }; int pos[2] = { xpos, ypos };
        ypos += (screenSurface->h / rectangles);
        xpos -= (screenSurface->w / rectangles);
        //////////////Create Starting Objects
        SplashRectangle* newRectangle = new SplashRectangle(size, pos, &speed);
        splashArray.push_back(*newRectangle);
        //////////////
    }
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t o = 0; o < splashFrames/4; o++)
        {
            start = SDL_GetPerformanceCounter();
            SDL_RenderPresent(renderer);
            SDL_SetRenderDrawColor(renderer, 250, 158, 2, 255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 251, 188, 79, 255);
            list<SplashRectangle>::iterator it;
            for (it = splashArray.begin(); it != splashArray.end(); ++it)
            {
                it->Move(right);
                DrawCharacter(&(*it));
            }
            end = SDL_GetPerformanceCounter();
            float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
            cout << elapsedMS << endl;
            SDL_Delay(floor((5000 / splashFrames) - elapsedMS));
            //SDL_Delay(100);
            //SDL_RenderPresent(renderer);
        }
        //int tempX = 
        list<SplashRectangle>::iterator it;
        for (it = splashArray.begin(); it != splashArray.end(); ++it)
        {
            int newPos[2] = { it->GetPosX(), (it->GetSizeH()*rectangles) - it->GetPosY() - it->GetSizeH() };
            cout << "creee" << screenSurface->h - it->GetPosY() - it->GetSizeH() << endl;
            it->SetPosition(newPos);
        }
        right = !right;
    }
}
