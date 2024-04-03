#include "Collision.h"
#include "GameEngine.h"

Collision::Collision()
{
}

Collision::~Collision()
{
}

void Collision::Init(GameEngine* _parent)
{
	parent = _parent;
	for (int i = 0; i < hitZoneDepth; i++)
	{
		hitZonesX.push_back((parent->GWindow.GetWindow()->w / hitZoneDepth) * i);
	}
	for (int i = 0; i < hitZoneDepth; i++)
	{
		hitZonesY.push_back((parent->GWindow.GetWindow()->h / hitZoneDepth) * i);
	}
	for (int i = 0; i < hitZoneDepth; i++)
	{
		cout << hitZonesX[i] << endl;
		cout << hitZonesY[i] << endl;
	}
}

void Collision::CalculateHitZone(Character* thisChar)
{
	for (int i = 0; i < hitZoneDepth; i++)
	{
		if (thisChar->GetPosX() > hitZonesX[i])
		{
			thisChar->collisionZone[0] = i;
		}
	}
	for (int i = 0; i < hitZoneDepth; i++)
	{
		if (thisChar->GetPosY() > hitZonesY[i])
		{
			thisChar->collisionZone[1] = i;
		}
	}
}

void Collision::CheckCollision(Character* thisChar)
{
	int ThisLXBound = thisChar->GetPosX();
	int ThisRXBound = thisChar->GetPosX() + thisChar->GetSizeW();
	int ThisTYBound = thisChar->GetPosY();
	int ThisBYBound = thisChar->GetPosY() + thisChar->GetSizeH();
	int ListLXBound;
	int ListRXBound;
	int ListTYBound;
	int ListBYBound;
	for (int i = 0; i < parent->allcharacters.size(); i++)
	{
		if ((parent->allcharacters[i]->collisionZone[0] == thisChar->collisionZone[0]) && (parent->allcharacters[i]->collisionZone[1] == thisChar->collisionZone[1]))
		{
			if (parent->allcharacters[i]->GetSpawned())
			{
				if (parent->allcharacters[i] != thisChar)
				{
					ListLXBound = parent->allcharacters[i]->GetPosX();
					ListRXBound = parent->allcharacters[i]->GetPosX() + parent->allcharacters[i]->GetSizeW();
					ListTYBound = parent->allcharacters[i]->GetPosY();
					ListBYBound = parent->allcharacters[i]->GetPosY() + parent->allcharacters[i]->GetSizeH();
					if ((ThisRXBound > ListLXBound) && (ThisLXBound < ListRXBound))
					{
						if ((ThisTYBound < ListBYBound) && (ThisBYBound > ListTYBound))
						{
							thisChar->Collide(parent->allcharacters[i]);
						}
					}
				}
			}
		}
	}
}
