#include "GameEngine.h"


/// <summary>
/// this constructor starts the game and it's loop
/// </summary>
GameEngine::GameEngine(SDL_Window* window)
    : ImageRender(window, this),
    SoundPlayer(this),
    aTimer(this)
{
    SoundPlayer.MusicLocationVector = { "Sounds/PUNK_SKATE_TO-KNIGHT_OK_PROD._PAYMAN_192BPM.mp3"};
    SoundPlayer.MusicVector.push_back(SoundPlayer.MixMusic(SoundPlayer.MusicLocationVector[0]));
    //Mix_PlayMusic(SoundPlayer.MusicVector[0], 0);
    GWindow = GameWindow(ImageRender.GetSurface(), this);
    Collider.Init(this);
    //screenSurface = SDL_GetWindowSurface(window);
    //ImageRender = ImageRenderer(window);
    int speed = 0;
    int size[2] = { GWindow.GetWindow()->w, GWindow.GetWindow()->h }; int pos[2] = {GWindow.GetWindow()->w / 2, GWindow.GetWindow()->h / 2};
    Background = new SplashRectangle(size, pos, &speed);
    Background->Init(this);
    int size2[2] = { 64, 64 }; int pos2[2] = { ImageRender.GetSurface()->w / 2,ImageRender.GetSurface()->h - (ImageRender.GetSurface()->h / 8)};
    //////////////Create Main Character
    SirRad = new Player(size2, pos2, &speed, "Images/SirRadSheet.png");
    SirRad->Init(this);
    enemyContainers.push_back(new EnemyContainer(10, EnemyContainer::fireball, 5, 3, this));
    enemyContainers.push_back(new EnemyContainer(10, EnemyContainer::orc, 10, 10, this));
    enemyContainers.push_back(new EnemyContainer(10, EnemyContainer::axe, -1, -1, this));
    TTF_Init();
    Sans = TTF_OpenFont("Text/RujisHandwritingFontV20-vrqZ.ttf", 24);
    /*SDL_Color textColour = { 255, 255, 255 };
    string textMessage = "SCORE: " + to_string(GameScore);
    surfaceMessage = TTF_RenderText_Solid(Sans, textMessage.c_str(), textColour);
    Message = SDL_CreateTextureFromSurface(ImageRender.GetRenderer(), surfaceMessage);*/
    //SirRad.parent = this;
    ////Initialise the game image renderer
    //////////////
    PrintLog("splash screen is running");
    Splash(); //do the splash screen at the start of the game
    //GameOfLife newLife;
    //Life = &newLife.Create(screenSurface->w, screenSurface->h, renderer);
    //ColourGame newGame;
    // game = &newGame.Create(renderer);
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
        //Handle events on queue

        //Clear screen
        //SDL_RenderClear(gRenderer);

        //Render texture to screen
        //SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

        //Update screen
        //SDL_RenderPresent(gRenderer);
        totalTime += 16.667;
        if(16.667 - aTimer.getTicks() < 0)
        {
            PrintLog("FrameRate: " + to_string(aTimer.getTicks()));
        }
        else 
        {
            PrintLog("FrameRate: 16.667"); //print 16.667 if get ticks is less than 16.667 since delay sets the framerate to this valued
        }
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
    if (totalTime > 80000) {
        quit = true;
        PrintLog("Your score was " + to_string(GameScore));
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
        //////////////Create Starting Objects
        SplashRectangle* newRectangle = new SplashRectangle(size, pos, &speed);
        newRectangle->Init(this);
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
                it->Move();
                ImageRender.DrawCharacter(&(*it));
            }
            SDL_Delay(floor((5000 / splashFrames) - aTimer.getTicks()));
            totalTime += 16.667;
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
