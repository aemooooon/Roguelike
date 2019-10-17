#include "Sprite.h"

Sprite::Sprite(Graphics^ startCanvas, array<Bitmap^>^ startSpriteSheets, int startNFrames, Random^ startRGen)
{
	rGen = startRGen;

	// put four direction of Sprite
	spriteSheets = gcnew array<Bitmap^>(MAX_DIRECTIONS);
	for (int i = 0; i < MAX_DIRECTIONS; i++)
	{
		spriteSheets[i] = gcnew Bitmap(startSpriteSheets[i]);
		spriteSheets[i]->MakeTransparent(spriteSheets[i]->GetPixel(0, 0));
	}

	spriteDirection = (EDirection)rGen->Next(4); //by default EDirection::EAST;

	// dynamic direction
	velocityDirections = gcnew array<Point>(MAX_DIRECTIONS);
	velocityDirections[0] = Point(1, 0);
	velocityDirections[1] = Point(0, 1);
	velocityDirections[2] = Point(-1, 0);
	velocityDirections[3] = Point(0, -1);

	canvas = startCanvas;
	currentFrame = startNFrames;

	nFrames = startNFrames;
	xPos = 400;
	yPos = 300;
	frameWidth = (int)spriteSheets[0]->Width / nFrames;
	frameHeight = spriteSheets[0]->Height;
	xVel = 0;
	yVel = 0;

	isAlive = true;

}

// draw sprite
void Sprite::Draw()
{
	int currFrameX = currentFrame * frameWidth;
	int currFrameY = 0;

	Rectangle drawRect = Rectangle(currFrameX, currFrameY, frameWidth, frameHeight);

	Bitmap^ currentBitmap = spriteSheets[spriteDirection];

	canvas->DrawImage(currentBitmap, xPos, yPos, drawRect, GraphicsUnit::Pixel);


}

// based on viewport moving, force draw player each time to fixed Point
void Sprite::ForcedDraw(int forcedX, int forcedY)
{
	int currFrameX = currentFrame * frameWidth;
	int currFrameY = 0;

	Rectangle drawRect = Rectangle(currFrameX, currFrameY, frameWidth, frameHeight);

	Bitmap^ currentBitmap = spriteSheets[spriteDirection];

	canvas->DrawImage(currentBitmap, forcedX, forcedY, drawRect, GraphicsUnit::Pixel);

}

void Sprite::Erase()
{

}

void Sprite::Move()
{
	xPos += xVel * velocityDirections[spriteDirection].X;
	yPos += yVel * velocityDirections[spriteDirection].Y;
}

void Sprite::Move(TileMap^ tileMap)
{
	// check the tiles walkable
	int tempX = velocityDirections[spriteDirection].X * xVel + xPos;
	int tempY = velocityDirections[spriteDirection].Y * yVel + yPos;
	int temp = frameWidth * 0.2;
	switch (spriteDirection)
	{
		case 0:
			tempX = frameWidth - temp + tempX;
			tempY = frameHeight - temp + tempY;
			break;
		case 1:
			tempX = temp + tempX;
			tempY = frameHeight - temp + tempY;
			break;
		case 2:
			tempX = temp + tempX;
			tempY = frameHeight - temp + tempY;
			break;
		case 3:
			tempX = temp + tempX;
			tempY = temp + tempY;
			break;
	}

	//check if tiles not walkable then change direction to opposit
	if (tileMap->IsWalkable(tempX / frameWidth, tempY / frameHeight))
	{
		xPos += velocityDirections[spriteDirection].X * xVel;
		yPos += velocityDirections[spriteDirection].Y * yVel;
	}
	else
	{
		// Change direction to opposite
		spriteDirection = (EDirection)((spriteDirection + 2) % 4);
		return;
	}

}

// set sprite sheets loop display
void Sprite::UpdateFrame()
{
	//++currentFrame %= nFrames;
	currentFrame = (currentFrame + 1) % nFrames;
}

void Sprite::SetSpriteSheet(Bitmap^ newSpriteSheet, int newNFrames)
{

}

//Sprite has 49% change to change direction to move
void Sprite::Wander()
{
	if (rGen->Next(49) == 0)
		xVel *= -1;
	if (rGen->Next(49) == 0)
		yVel *= -1;

	Move();
}

//Sprite has 50% change to change direction to move with tilemap
void Sprite::Wander(TileMap^ tileMap)
{
	Move(tileMap);

	if (rGen->Next(5) == 0)
	{
		xVel *= -1;
		spriteDirection = (EDirection)((spriteDirection + 2) % 4);
	}
		
	if (rGen->Next(5) == 0)
	{
		yVel *= -1;
		spriteDirection = (EDirection)((spriteDirection + 2) % 4);
	}

}

// chech angle between sprite to other
// its has 50% change to follow sprite in vertical or horizental
void Sprite::Orient(Sprite^ target)
{
	double angle = computeAngleToTarget(target);
	XVel = (int)(Math::Cos(angle) * 5);
	YVel = (int)(Math::Sin(angle) * 5);
}

// check Collide with other
// assume there two circle and with circle centre construct tow triangle
// to calculate two circle centre distance via triangle pricepal
// a2+b2=c2 power of a,b,c
bool Sprite::CollidedWithMe(Sprite^ otherGuy)
{
	int x1 = xPos;
	int x2 = otherGuy->xPos;
	int y1 = yPos;
	int y2 = otherGuy->YPos;
	int r1 = 37;
	int r2 = 16;
	return ((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)) < (r1 + r2)*(r1 + r2);
}

Rectangle^ Sprite::GetRectangle()
{
	return gcnew Rectangle(XPos, YPos, frameWidth, frameHeight);
}

double Sprite::computeAngleToTarget(Sprite^ target)
{
	double angle;

	int xDelta = target->XPos - xPos;
	int yDelta = target->YPos - yPos;

	if ((xDelta != 0) && (yDelta != 0))
	{
		// Check order of args
		// atan2 returns the angle of rotation between two points with vertical distance arg1 and horizontal distance arg2
		angle = Math::Atan2(yDelta, xDelta);	// result is in radians
	}
	else
		angle = 0.0;	// instance and target share an x or y axis location. This works as a heuristic

	return angle;
}
