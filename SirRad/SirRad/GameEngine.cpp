#include "GameEngine.h"


/// <summary>
/// this constructor starts the game and it's loop
/// </summary>
GameEngine::GameEngine(SDL_Window* window)
    : ImageRender(window)
{
    SoundPlayer.MusicLocationVector = { "Sounds/OnStackNew.wav"};
    SoundPlayer.MusicVector.push_back(SoundPlayer.MixMusic(SoundPlayer.MusicLocationVector[0]));
    GWindow = GameWindow(ImageRender.GetSurface());
    //screenSurface = SDL_GetWindowSurface(window);
    //ImageRender = ImageRenderer(window);
    int speed = 0;
    int size[2] = { 30, 30 }; int pos[2] = { ImageRender.GetSurface()->w / 2,ImageRender.GetSurface()->h - (ImageRender.GetSurface()->h / 8)};
    //////////////Create Main Character
    SirRad = Player(size, pos, &speed, "Images/Hi.png");
    SirRad.Init(this);
    //SirRad.parent = this;
    ////Initialise the game image renderer
    //////////////
    Splash(); //do the splash screen at the start of the game
    //GameOfLife newLife;
    //Life = &newLife.Create(screenSurface->w, screenSurface->h, renderer);
    //ColourGame newGame;
    // game = &newGame.Create(renderer);
    Mix_PlayMusic(SoundPlayer.MusicVector[0], -1);
    GameLoop(); ////always goes last probably
}

GameEngine::~GameEngine()
{
}

void GameEngine::GameLoop()
{
    while (!quit)
    {
        aTimer.resetTicksTimer();
        Input();
        Update();
        Render();
        //Handle events on queue

        //Clear screen
        //SDL_RenderClear(gRenderer);

        //Render texture to screen
        //SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

        //Update screen
        //SDL_RenderPresent(gRenderer);
        SDL_Delay(16.667 - aTimer.getTicks());
    }
}
void GameEngine::Input()
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
                MoveLeft = true;
                break;
            case SDLK_d:
                MoveRight = true;
                break;
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_a:
                MoveLeft = false;
                break;
            case SDLK_d:
                MoveRight = false;
                break;
            default:
                break;
            }
            break;

        default:
            //printf("event polled");
            break;
        }
    }
}
/// <summary>
/// the update of all values within the game
/// </summary>
void GameEngine::Update()
{
    SirRad.Movement(MoveLeft, MoveRight);
    SirRad.Move(true);
}
/// <summary>
/// the drawing of all objects within the game
/// </summary>
void GameEngine::Render()
{
    /////////////////////////draw background
    //game.
    SDL_SetRenderDrawColor(ImageRender.GetRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(ImageRender.GetRenderer());
    SDL_SetRenderDrawColor(ImageRender.GetRenderer(), 230, 122, 27, 255);
    DrawCharacter(&SirRad);
    /////////bbbbbbbbbbbbbbbbbbb/////////////s/// 
    SDL_RenderPresent(ImageRender.GetRenderer());
    //SDL_UpdateWindowSurface(ImageRender.GetWindow());
}

void GameEngine::DrawCharacter(Character* draw)
{
    SDL_Rect rect = { draw->GetPosX(), draw->GetPosY(), draw->GetSizeW(), draw->GetSizeH() };
    SDL_RenderFillRect(ImageRender.GetRenderer(), &rect);
    SDL_RenderDrawRect(ImageRender.GetRenderer(), &rect);
    if (draw->GetImagePath() != "None") {
        SDL_RenderCopy(ImageRender.GetRenderer(), draw->image_Texture, NULL, &rect);
    }
}

void GameEngine::Splash()
{
    aTimer.resetTicksTimer();
    float xpos = 0 - (ImageRender.GetSurface()->w*5);
    float ypos = 0;
    int rectangles = 6;
    bool right = true;
    float screenWidth = ImageRender.GetSurface()->w;
    float screenHeight = ImageRender.GetSurface()->h;
    list<SplashRectangle> splashArray;
    for (size_t i = 0; i < rectangles; i++)
    {
        ////////////////////////Setup Splash Square stats
        int speed = (screenWidth) / (splashFrames/(ImageRender.GetSurface()->w/ (screenWidth /8)));
        int size[2] = { (screenWidth *5), (ceil(screenHeight / rectangles)) }; int pos[2] = { xpos, ypos };
        ypos += ceil(screenHeight / rectangles);
        xpos -= ceil(screenWidth / rectangles);
        cout << "position: " << ypos << endl;
        //////////////Create Starting Objects
        SplashRectangle* newRectangle = new SplashRectangle(size, pos, &speed);
        splashArray.push_back(*newRectangle);
        //////////////
    }
    //////////////////////////////loop each frame drawing all splash cubes
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t o = 0; o < splashFrames/4; o++)
        {
            SDL_SetRenderDrawColor(ImageRender.GetRenderer(), 250, 158, 2, 255);
            SDL_RenderClear(ImageRender.GetRenderer());
            SDL_SetRenderDrawColor(ImageRender.GetRenderer(), 251, 188, 79, 255);
            list<SplashRectangle>::iterator it;
            for (it = splashArray.begin(); it != splashArray.end(); ++it)
            {
                it->Move(right);
                DrawCharacter(&(*it));
            }
            SDL_Delay(floor((5000 / splashFrames) - aTimer.getTicks()));
            aTimer.resetTicksTimer();
            SDL_RenderPresent(ImageRender.GetRenderer());
        }
        /////////////////////////////Swap cube positions
        //int tempX = 
        list<SplashRectangle>::iterator it;
        for (it = splashArray.begin(); it != splashArray.end(); ++it)
        {
            int newPos[2] = { it->GetPosX(), (it->GetSizeH()*rectangles) - it->GetPosY() - it->GetSizeH() };
            it->SetPosition(newPos);
        }
        right = !right;
    }
    //////////////////////
}
