#pragma once
#include "TileMap.h"

///////////////////////////////////////////////////////////////////////////////////////////////
// Single Sprite class
///////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_DIRECTIONS 4

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

// define direction as enum
public enum EDirection { EAST, SOUTH, WEST, NORTH };

ref class Sprite
{
protected:
	Graphics^ canvas;
	array<Bitmap^>^ spriteSheets;
	EDirection spriteDirection;
	array<Point>^ velocityDirections;

	Random^ rGen;
	int nFrames;
	int currentFrame;
	int xPos;
	int yPos;
	int frameWidth;
	int frameHeight;
	int xVel;
	int yVel;

	bool isAlive;


public:
	Sprite^ Next;

	property bool IsAlive
	{
		bool get()
		{
			return isAlive;
		}
		void set(bool d)
		{
			isAlive = d;
		}
	}

	property EDirection SpriteDirection
	{
		EDirection get()
		{
			return spriteDirection;
		}
		void set(EDirection d)
		{
			spriteDirection = d;
		}
	}

	property int XVel
	{
		int get()
		{
			return xVel;
		}
		void set(int d)
		{
			xVel = d;
		}
	}

	property int YVel
	{
		int get()
		{
			return yVel;
		}
		void set(int d)
		{
			yVel = d;
		}
	}

	property int XPos
	{
		int get()
		{
			return xPos;
		}
		void set(int d)
		{
			xPos = d;
		}
	}

	property int YPos
	{
		int get()
		{
			return yPos;
		}
		void set(int d)
		{
			yPos = d;
		}
	}

	Sprite(Graphics^ startCanvas, array<Bitmap^>^ startSpriteSheets, int startNFrames, Random^ startRGen);
	virtual void Draw();
	void Erase();
	void Move();
	void Move(TileMap^ tileMap);
	void UpdateFrame();
	void SetSpriteSheet(Bitmap^ newSpriteSheet, int newNFrames);
	void Wander();
	void Wander(TileMap^ tileMap);
	void ForcedDraw(int forcedX, int forcedY);
	bool CollidedWithMe(Sprite^ otherGuy);
	Rectangle^ GetRectangle();
	double computeAngleToTarget(Sprite^ target);
	void Orient(Sprite^ target);
};

