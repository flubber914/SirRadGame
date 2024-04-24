#include "GameOfLife.h"

GameOfLife::GameOfLife()
{
	CreateLife();
}

GameOfLife::GameOfLife(int width, int height, SDL_Renderer* _renderer)
{
	//CreateLife();
	screenHeight = height;
	screenWidth = width;
	renderer = _renderer;
}

GameOfLife::~GameOfLife()
{
}

GameOfLife& GameOfLife::Create(int width, int height, SDL_Renderer* _renderer)
{
	return *(new GameOfLife(width, height, _renderer));
}

void GameOfLife::ScreenClick(int x, int y)
{
	if (x < screenHeight && y < screenHeight)
	{
		grid[y / (screenHeight / Ysize)][x / (screenHeight / Xsize)] = true;
		printf("eh?");
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
	int speed = 0;
	int size[2] = { (screenHeight / Xsize), (screenHeight / Ysize) }; int pos[2] = { 0, 0 };
	SplashRectangle* LifeSquare = new SplashRectangle(size, pos, &speed);
	for (int i = 0; i < Ysize; i++)
	{
		for (int o = 0; o < Xsize; o++)
		{
			if (grid[i][o])
			{
				int newPos[2] = { o * size[0] , i * size[1] };
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
