#include "Character.h"
#include "GameEngine.h"

Character::Character()
{
	size[0] = 10; size[1] = 10;
	position[0] = 10; position[1] = 10;
	speed = 2;
}
/// <summary>
/// this constructor sets character statistics
/// </summary>
Character::Character(int _size [2], int _position [2], int* _speed, string _ImagePath, int _spriteRows)
{
	size[0] = _size[0]; size[1] = _size[1];
	position[0] = _position[0]; position[1] = _position[1];
	speed = *_speed;
	ImagePath = _ImagePath;
	character_Surface = SDL_CreateRGBSurface(0, GetSizeW(), GetSizeH(), 32, 0, 0, 0, 0);
	spriteRows = _spriteRows;

}
/// <summary>
/// this virtual constructor for the virtual class Character
/// </summary>
Character::~Character()
{
}
/// <summary>
/// This virual Function is the basis of all movement of all characters in the game
/// </summary>
/// <returns></returns>
bool Character::Move()
{
	return false;
}

void Character::Collide(Character* other)
{
}

void Character::FindCollisionZone()
{
	parent->Collider.CalculateHitZone(this);
}

void Character::Init(GameEngine* _parent)
{
	parent = _parent;
	if (ImagePath != "None") {
		image_Texture = SDL_CreateTextureFromSurface(parent->ImageRender.GetRenderer(), parent->ImageRender.loadSurface(ImagePath));
		if (image_Texture != NULL && spriteRows != 0) 
		{
			LoadSprites();
		}
	}
	parent->allcharacters.push_back(this);
}

void Character::ChangeDirection(int _direction)
{
}

void Character::Animate()
{
	if ((parent->totalTime - lastFrame) > 250)
	{
		CurrentSpriteClip = (((currentAnimation - 1) * 4) + currentFrame);
		currentFrame++;
		if (currentFrame == 5) {
			currentFrame = 0;
		}
		lastFrame = parent->totalTime;
	}
}

void Character::LoadSprites()
{
	if (image_Texture != NULL) 
	{
		int width = parent->ImageRender.loadSurface(ImagePath)->w / 4;
		int height = parent->ImageRender.loadSurface(ImagePath)->h/spriteRows;
		SDL_Rect printRect;
		for (int i = 0; i < spriteRows; i++)
		{
			for (int o = 0; o < 4; o++)
			{
				printRect.x = width * o;
				printRect.y = height * i;
				printRect.w = width;
				printRect.h = height;
				SpriteClips.push_back(printRect);
			}
		}
	}
	else 
	{
		cout << "ERROR: no texture for spritesheet creation" << endl;
	}
}
