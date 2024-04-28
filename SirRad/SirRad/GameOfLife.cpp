#include "GameOfLife.h"
#include "GameEngine.h"

GameOfLife::GameOfLife(GameEngine* _parent)
{
	parent = _parent;
	CreateLife();
}

GameOfLife::GameOfLife(int width, int height, SDL_Renderer* _renderer, GameEngine* _parent)
{
	parent = _parent;
	//CreateLife();
	screenHeight = parent->GWindow.GetWindow()->h;
	screenWidth = parent->GWindow.GetWindow()->w;
	renderer = _renderer;
	int speed = 0;
	int size[2] = { (screenWidth / Xsize), (screenHeight / Ysize) }; int pos[2] = { 0, 0 };
	LifeSquare = new SplashRectangle(size, pos, &speed, "None");
	LifeSquare->Init(parent);
}

GameOfLife::~GameOfLife()
{
	cout << "GameOfLife Is Over!" << endl;
	delete LifeSquare;
}

GameOfLife& GameOfLife::Create(int width, int height, SDL_Renderer* _renderer, GameEngine* _parent)
{
	return *(new GameOfLife(width, height, _renderer, _parent));
}

void GameOfLife::ScreenClick(int x, int y)
{
	if (x < screenHeight && y < screenHeight)
	{
		grid[y / (screenHeight / Ysize)][x / (screenWidth / Xsize)] = true;
	}
}

void GameOfLife::CreateLife()
{
	srand(time(0));
	for (int i = 0; i < Ysize; i++)
	{
		for (int o = 0; o < Xsize; o++)
		{
			grid[i][o] = GetRandomBool();
		}
	}
}

void GameOfLife::DrawLife()
{
	for (int i = 0; i < Ysize; i++)
	{
		for (int o = 0; o < Xsize; o++)
		{
			if (grid[i][o])
			{
				int newPos[2] = { o * LifeSquare->GetSizeW() , i * LifeSquare->GetSizeH() };
				LifeSquare->SetPosition(newPos);
				DrawCharacter(LifeSquare);
			}
		}
	}
}

void GameOfLife::DrawCharacter(Character* draw)
{
	SDL_Rect rect = { draw->GetPosX(), draw->GetPosY(), draw->GetSizeW(), draw->GetSizeH() };

	SDL_RenderFillRect(renderer, &rect);
	//SDL_RenderDrawRect(renderer, &rect);

	//SDL_RenderDrawRect(renderer, &rect);
}

void GameOfLife::ChangeLife()
{
	int nextAmount;
	bool newGrid[Xsize][Ysize];
	memcpy(newGrid, grid, sizeof(newGrid));
	for (int i = 0; i < Ysize; i++)
	{
		for (int o = 0; o < Xsize; o++)
		{
			nextAmount = 0;
			for (int a = -1; a < 2; a++)
			{
				if (o + a < 0 || o + a == Xsize)
				{
					continue;
				}
				for (int b = -1; b < 2; b++)
				{
					if (i + b < 0 || i + b == Ysize)
					{
						continue;
					}
					if (grid[i + b][o + a])
					{
						if (b != 0 || a != 0) 
						{
							nextAmount++;
						}
					}
				}
			}
			if (grid[i][o])
			{
				if (nextAmount == 2 || nextAmount == 3)
				{
					newGrid[i][o] = true;
				}
				/*if (nextAmount == 3)
				{
					grid[i][o] = true;
				}*/
				else
				{
					newGrid[i][o] = false;
				}
			}
			else 
			{
				if (nextAmount == 3) 
				{
					newGrid[i][o] = true;
				}
			}
		}
	}
	memcpy(grid, newGrid, sizeof(grid));
}

bool GameOfLife::GetRandomBool()
{
	return (rand() % 15);
}
