#pragma once
#include "Sprite.h"

// define State as enum
public enum ESpriteState { WANDERING, FIGTHING, ORIENTING };

ref class KnightSprite: public Sprite
{
private:
	ESpriteState spriteState;
	int fightingTicks;
	int wanderingTicks;

public:
	KnightSprite(Graphics^ startCanvas, array<Bitmap^>^ startSpriteSheets, int startNFrames, Random^ startRGen);
	virtual void Draw() override;
	void UpdateState(array<Sprite^>^ yellowSpriteList);
	void PerformAction(TileMap^ tileMap);
};

