#include "KnightSprite.h"

// KnightSprite class inherit from Sprite class and overide the Draw methods.

KnightSprite::KnightSprite(Graphics ^ startCanvas, array<Bitmap^>^ startSpriteSheets, int startNFrames, Random ^ startRGen)
	: Sprite(startCanvas, startSpriteSheets, startNFrames, startRGen)
{
	
}

void KnightSprite::Draw()
{
	int currFrameX = currentFrame * frameWidth;
	int currFrameY = 0;

	Rectangle drawRect = Rectangle(currFrameX, currFrameY, frameWidth, frameHeight);

	Bitmap^ currentBitmap = spriteSheets[spriteDirection];

	canvas->DrawImage(currentBitmap, xPos, yPos, drawRect, GraphicsUnit::Pixel);
}


// loop all SpriteList and check in different State
void KnightSprite::UpdateState(array<Sprite^>^ yellowSpriteList)
{
	switch (spriteState)
	{
	case WANDERING:
		for (int i = 0; i < yellowSpriteList->Length; i++)
		{
			if (yellowSpriteList[i]->CollidedWithMe(this))
			{
				spriteState = FIGTHING;
			}
		}
		break;
	case FIGTHING:
		for (int i = 0; i < yellowSpriteList->Length; i++)
		{
			if (!yellowSpriteList[i]->IsAlive)
			{
				spriteState = WANDERING;
			}
		}
		break;
	case ORIENTING:
	Orient(this);
		break;
	}
}

// according to state to run action
void KnightSprite::PerformAction(TileMap^ tileMap)
{
	switch (spriteState)
	{
	case WANDERING:
		Wander(tileMap);
		break;
	case FIGTHING:
		XVel = 0;
		YVel = 0;
		break;
	case ORIENTING:
		Orient(this);
		break;
	}
}
