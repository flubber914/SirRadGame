#include "GameEngine.h"


/// <summary>
/// this constructor starts the game and it's loop
/// </summary>
GameEngine::GameEngine(SDL_Window* window)
    : ImageRender(window, this),
    SoundPlayer(this),
    aTimer(this)
{
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SoundPlayer.MusicLocationVector = { "Sounds/SirRadSong.ogg"};
    SoundPlayer.MusicVector.push_back(SoundPlayer.MixMusic(SoundPlayer.MusicLocationVector[0]));
    Mix_PlayMusic(SoundPlayer.MusicVector[0], 0);
    GWindow = GameWindow(ImageRender.GetSurface(), this, window);
    Collider.Init(this);

    PrintLog("splash screen is running");
    splashLife = new GameOfLife(100, 100, ImageRender.GetRenderer(), this);
    &splashLife->Create(100,100, ImageRender.GetRenderer(), this);
    SDL_RenderSetLogicalSize(ImageRender.GetRenderer(), 800, 450);
    Splash();

    int speed = 0;
    int size[2] = { GWindow.GetWindow()->w, GWindow.GetWindow()->h }; int pos[2] = { GWindow.GetWindow()->w / 2, GWindow.GetWindow()->h / 2 };
    Background = new SplashRectangle(size, pos, &speed, "Images/Background.png");
    Background->Init(this);

    int size2[2] = { 64, 64 }; int pos2[2] = { ImageRender.GetSurface()->w / 2,ImageRender.GetSurface()->h - (ImageRender.GetSurface()->h / 8) };
    //////////////Create Main Character
     SirRad = new Player(size2, pos2, &speed, "Images/SirRadSheet.png");
    SirRad->Init(this);
    enemyContainers.push_back(new EnemyContainer(10, EnemyContainer::fireball, 21.5, 1.25, this));
    enemyContainers.push_back(new EnemyContainer(10, EnemyContainer::orc, 30, 5, this));
    enemyContainers.push_back(new EnemyContainer(10, EnemyContainer::axe, -1, -1, this));
    TTF_Init();
    Sans = TTF_OpenFont("Text/RujisHandwritingFontV20-vrqZ.ttf", 24);
    Message_rect.x = 0;
    Message_rect.y = 0;
    Message_rect.w = 100;
    Message_rect.h = 50;
    PrintLog("Game proper is starting");
    GameLoop(); ////always goes last
}

GameEngine::~GameEngine()
{
    TTF_CloseFont(Sans);
    PrintLog("Deleting everything ------------------------------");
    PrintLog("Text Unloaded");
    for (int i = 0; i < 3; i++)
    {
        delete enemyContainers[5-(i*2)];
    }
    //SDL_FreeSurface(surfaceMessage);
    delete Background;
    delete SirRad;

    SDL_DestroyTexture(Message);
    TTF_Quit();
    PrintLog("GameEngine Unloaded -----------------------------");
}

void GameEngine::ChangeScore(int change)
{
    GameScore += change;
}

void GameEngine::PrintLog(string text)
{
    if (isLogging)
    {
        cout << text << endl;
    }
}

void GameEngine::GameLoop()
{
    while (!quit)
    {
        aTimer.resetTicksTimer();
        Input();
        Update();
        Render();
        totalTime += 16.667;
        if(16.667 - aTimer.getTicks() < 0)
        {
            PrintLog("FrameRate: " + to_string(aTimer.getTicks()));
        }
        else 
        {
            PrintLog("FrameRate: 16.667"); //print 16.667 if get ticks is less than 16.667 since delay sets the framerate to this valued
            SDL_Delay(16.667 - aTimer.getTicks());
        }
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
                quit = true;
                break;
            case SDLK_a:
                PrintLog("a pressed to move left");
                MoveLeft = true;
                SirRad->currentAnimation = 2;
                SirRad->performingTrick = false;
                break;
            case SDLK_d:
                PrintLog("d pressed to move right");
                MoveRight = true;
                SirRad->currentAnimation = 2;
                SirRad->performingTrick = false;
                break;
            case SDLK_q:
                PrintLog("q pressed to ollie");
                SirRad->DoTrick(3);
                break;
            case SDLK_e:
                PrintLog("e pressed to christ");
                SirRad->DoTrick(4);
                break;
            case SDLK_f:
                PrintLog("f pressed to flip");
                SirRad->DoTrick(5);
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_a:
                PrintLog("a lifted to stop move left");
                MoveLeft = false;
                SirRad->currentAnimation = 1;
                break;
            case SDLK_d:
                PrintLog("d lifted to stop move right");
                MoveRight = false;
                SirRad->currentAnimation = 1;
                break;
            case SDLK_l:
                PrintLog("is still logging: " + to_string(!isLogging));
                isLogging = !isLogging;
                break;
            case SDLK_p:
                if (isFullscreen) {
                    SDL_SetWindowFullscreen(GWindow.GetScreen(), 0);
                    isFullscreen = false;
                }
                else {
                    SDL_SetWindowFullscreen(GWindow.GetScreen(), SDL_WINDOW_FULLSCREEN_DESKTOP);
                    isFullscreen = true;
                }
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
    SirRad->Movement(MoveLeft, MoveRight);
    SirRad->Move();
    SirRad->ChangeDirection(0);
    SirRad->Animate();
    UpdateContainers();
    PrintLog("Currently in Main Game");
    if (totalTime > 80000) {
        quit = true;
        PrintLog("Quit with overtime");
        PrintLog("Your score was " + to_string(GameScore));
    }
    else if (totalTime > 65000 && GameScore < 30000) /////////////This is overtime
    {
        quit = true;
        PrintLog("Quit without overtime");
        PrintLog("Your score was " + to_string(GameScore));
    }
    if (totalTime > 65000) {
        PrintLog("Currently in Overtime");
    }
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
    SDL_SetRenderDrawColor(ImageRender.GetRenderer(), 0, 0, 0, 0);
    ImageRender.DrawCharacter(Background, 0);
    ImageRender.DrawCharacter(SirRad, &SirRad->SpriteClips[SirRad->CurrentSpriteClip]);
    RenderContainers();
    DrawText();
    /////////bbbbbbbbbbbbbbbbbbb/////////////s/// 
    SDL_RenderPresent(ImageRender.GetRenderer());
    //SDL_UpdateWindowSurface(ImageRender.GetWindow());
}

void GameEngine::Splash()
{
    while (!quit)
    {
        aTimer.resetTicksTimer();
        SplashUpdate();
        SplashRender();
        totalTime += 16.667;
        if (16.667 - aTimer.getTicks() < 0)
        {
            PrintLog("FrameRate: " + to_string(aTimer.getTicks()));
        }
        else
        {
            PrintLog("FrameRate: 16.667"); //print 16.667 if get ticks is less than 16.667 since delay sets the framerate to this valued
            SDL_Delay(16.667 - aTimer.getTicks());
        }
        PrintLog("Currently in SplashScreen");
        if (totalTime > 5000) {
            PrintLog("Quit Splash Screen");
            quit = true;
        }
    }
    delete splashLife;
    PrintLog("Splash deleted");
    quit = false;
}

void GameEngine::SplashUpdate()
{
    if (count == 8)
    {
        splashLife->ChangeLife();
        count = 0;
    }
    else {
        count++;
    }
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            SDL_Quit();
            quit = true;
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == (SDL_BUTTON_LEFT))
            {
                leftMousePressed = true;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == (SDL_BUTTON_LEFT))
            {
                leftMousePressed = false;
            }
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_l:
                PrintLog("is still logging: " + to_string(!isLogging));
                isLogging = !isLogging;
                break;
            case SDLK_p:
                if (isFullscreen) {
                    SDL_SetWindowFullscreen(GWindow.GetScreen(), 0);
                    isFullscreen = false;
                }
                else {
                    SDL_SetWindowFullscreen(GWindow.GetScreen(), SDL_WINDOW_FULLSCREEN_DESKTOP);
                    isFullscreen = true;
                }
                break;
            }
            break;
        default:
            //printf("event polled");
            break;
        }
    }
    if (leftMousePressed)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        splashLife->ScreenClick(x, y);
    }
}

void GameEngine::SplashRender()
{
    /////////////////////////draw background
    SDL_SetRenderDrawColor(ImageRender.GetRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(ImageRender.GetRenderer());
    ///////////////////////// 
    SDL_SetRenderDrawColor(ImageRender.GetRenderer(), 255, 0, 255, 255);
    splashLife->DrawLife();
    //DrawCharacter(&SirRad);///////////DrawPlayer
    SDL_RenderPresent(ImageRender.GetRenderer());
}

void GameEngine::UpdateContainers()
{
    for (int i = 0; i < enemyContainers.size(); i++)
    {
        if (enemyContainers[i]->GetSpawnWait() != -1000)
        {
            enemyContainers[i]->Spawn();
        }
        enemyContainers[i]->ControlContained();
        enemyContainers[i]->AnimateContained();
    }
}

void GameEngine::RenderContainers()
{
    for (int i = 0; i < enemyContainers.size(); i++)
    {
        enemyContainers[i]->RenderContained();
    }
}

void GameEngine::DrawText()
{
    SDL_RenderCopy(ImageRender.GetRenderer(), Message, NULL, &Message_rect);
    if (("SCORE: " + to_string(GameScore)) != (textMessage))
    {
        SDL_DestroyTexture(Message);
        //Sans = TTF_OpenFont("Text/RujisHandwritingFontV20-vrqZ.ttf", 24);
        textColour = { 255, 255, 255 };
        textMessage = "SCORE: " + to_string(GameScore);
        surfaceMessage = TTF_RenderText_Solid(Sans, textMessage.c_str(), textColour);
        Message = SDL_CreateTextureFromSurface(ImageRender.GetRenderer(), surfaceMessage);
        SDL_FreeSurface(surfaceMessage);
    }
}
