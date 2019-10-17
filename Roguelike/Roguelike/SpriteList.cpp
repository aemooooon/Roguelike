#include "SpriteList.h"

// Linkd list constuctor 
SpriteList::SpriteList()
{
	// by default set up head and tail with null pointer
	head = nullptr;
	tail = nullptr;
}

// add a new sprite to linked list
// check from null pointer begining and not
void SpriteList::AddSprite(Sprite^ newSprite)
{
	if (tail == nullptr)
	{
		head = newSprite;
		tail = newSprite;
	}
	else
	{
		tail->Next = newSprite;
		tail = newSprite;
	}
}



void SpriteList::DeleteOneSprite(Sprite^ spriteToDelete)
{
	Sprite^ nodeWalker;
	nodeWalker = head;
	if (head == tail)
	{
		head, tail = nullptr;
	}
	else if (head == spriteToDelete)
	{
		head = head->Next;
	}
	else
	{
		while (nodeWalker->Next != spriteToDelete)
		{
			nodeWalker = nodeWalker->Next;

		}

		nodeWalker->Next = spriteToDelete->Next;

		// check the timer seems like stop
		if (nodeWalker->Next == nullptr)
		{
			tail = nodeWalker;
		}

	}
}

// loop all members and delete all of them
void SpriteList::DeleteAllSprites()
{
	Sprite^ nodeWalker;
	nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		Sprite^ tempWalker = nodeWalker;
		nodeWalker = nodeWalker->Next;
		DeleteOneSprite(tempWalker);
	}
}

//loop all members and call move method of single sprite
void SpriteList::MoveSprites()
{
	Sprite^ nodeWalker;
	nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		nodeWalker->Move();
		nodeWalker = nodeWalker->Next;
	}
}

//loop all members and call Wander method of single sprite
void SpriteList::WanderSprites()
{
	Sprite^ nodeWalker;
	nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		nodeWalker->Wander();
		nodeWalker = nodeWalker->Next;
	}
}

void SpriteList::WanderSprites(TileMap^ tileMap)
{
	Sprite^ nodeWalker;
	nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		nodeWalker->Wander(tileMap);
		nodeWalker = nodeWalker->Next;
	}
}

//loop all members and call move method of single sprite with tilemap
void SpriteList::WanderSprites(TileMap^ tileMap, Sprite^ target)
{
	Sprite^ nodeWalker;
	nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		nodeWalker->Orient(target);
		nodeWalker->Move(tileMap);

		nodeWalker->UpdateFrame();
		nodeWalker->Draw();

		nodeWalker = nodeWalker->Next;
	}
}

void SpriteList::MoveSprites(TileMap^ tileMap)
{
	Sprite^ nodeWalker;
	nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		nodeWalker->Move(tileMap);
		nodeWalker = nodeWalker->Next;
	}
}

void SpriteList::DrawSprites()
{
	Sprite^ nodeWalker;
	nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		nodeWalker->Draw();
		nodeWalker = nodeWalker->Next;
	}
}

void SpriteList::UpdateFrame()
{
	Sprite^ nodeWalker;
	nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		nodeWalker->UpdateFrame();
		//nodeWalker->Move();
		nodeWalker = nodeWalker->Next;
	}
}

int SpriteList::CountSprites()
{
	Sprite^ nodeWalker = head;

	int count = 0;
	while (nodeWalker != nullptr)
	{
		count++;
		nodeWalker = nodeWalker->Next;
	}
	return count;
}

void SpriteList::DrawSpritesInViewport(int  vWorldX, int vWorldY, int vPixelWidth, int vPixelHight)
{
	for (Sprite^ spriteWalker = head; spriteWalker != nullptr; spriteWalker = spriteWalker->Next)
	{
		if (spriteWalker->IsAlive == false)
		{
			DeleteOneSprite(spriteWalker);
		}
		else
		{
			// here is the fog of war implementation
			int screenX = spriteWalker->XPos - vWorldX;
			int screenY = spriteWalker->YPos - vWorldY;
			if ((spriteWalker->XPos > vWorldX+224 && spriteWalker->XPos < vWorldX + vPixelWidth-256) &&
				(spriteWalker->YPos > vWorldY+160 && spriteWalker->YPos < vWorldY + vPixelHight-192))
			{
				spriteWalker->ForcedDraw(screenX, screenY);
			}
		}

	}
}

bool SpriteList::CheckCollisionsWithBoss(Sprite^ otherGuy)
{
	Sprite^ sprite = head;
	bool flag = false;
	if (sprite != nullptr)
	{
		while (!flag)
		{
			if (sprite->CollidedWithMe(otherGuy))
			{
				flag = true;
			}
			else
			{
				sprite = sprite->Next;
			}
			if (sprite == nullptr)
			{
				break;
			}
		}
	}
	return flag;
}

void SpriteList::Stop()
{
	Sprite^ nodeWalker;
	nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		nodeWalker->XVel = 0;
		nodeWalker->YVel = 0;

		nodeWalker = nodeWalker->Next;
	}
}

bool SpriteList::Intersection(Sprite^ otherGuy)
{
	Sprite^ sprite = head;
	bool flag = false;
	if (sprite != nullptr)
	{
		while (!flag)
		{
			if (sprite->GetRectangle()->IntersectsWith((Rectangle)otherGuy->GetRectangle()))
			{
				flag = true;
			}
			else
			{
				sprite = sprite->Next;
			}
			if (sprite == nullptr)
			{
				break;
			}
		}
	}
	return flag;
}

bool SpriteList::CheckCollisions(Sprite^ otherGuy)
{
	Sprite^ sprite = head;
	bool flag = false;
	if (sprite != nullptr)
	{
		while (!flag)
		{
			if (sprite->CollidedWithMe(otherGuy))
			{
				flag = true;
				sprite->IsAlive = false;
			}
			else
			{
				sprite = sprite->Next;
			}
			if (sprite == nullptr)
			{
				break;
			}
		}
	}
	return flag;
}

void SpriteList::orient(Sprite^ target)
{
	Sprite^ nodeWalker;
	nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		double angle = nodeWalker->computeAngleToTarget(target);
		nodeWalker->XVel = (int)(Math::Cos(angle)*5);
		nodeWalker->YVel = (int)(Math::Sin(angle)*5);

		nodeWalker = nodeWalker->Next;
	}


}