#pragma once
#include "Sprite.h"
///////////////////////////////////////////////////////////////////////////////////////////////
// SpriteList holds a collection of Sprite via linkd list data structure
///////////////////////////////////////////////////////////////////////////////////////////////
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class SpriteList
{
private:
	Sprite^ head;
	Sprite^ tail;
public:
	SpriteList(void);
	void AddSprite(Sprite^ newSprite);
	void DeleteOneSprite(Sprite^ spriteToDelete);
	void DeleteAllSprites();
	void MoveSprites();
	void WanderSprites();
	void WanderSprites(TileMap^ tileMap);
	void MoveSprites(TileMap^ tileMap);
	void DrawSprites();
	void UpdateFrame();
	int CountSprites();
	void DrawSpritesInViewport(int  vWorldX, int vWorldY, int vPixelWidth, int vPixelHight);
	bool CheckCollisions(Sprite^ otherGuy);
	bool CheckCollisionsWithBoss(Sprite^ otherGuy);
	void orient(Sprite ^ target);
	void WanderSprites(TileMap^ tileMap, Sprite^ target);
	bool Intersection(Sprite^ otherGuy);
	void Stop();
};

