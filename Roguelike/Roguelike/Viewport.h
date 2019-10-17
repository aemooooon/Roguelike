#pragma once
#include "TileMap.h"
// Viewport class to dynamic calcula view centre of the world map
ref class Viewport
{
private:
	int viewportTilesWide;
	int viewportTilesHigh;

	int viewportWorldX;
	int viewportWorldY;

	int tileWidth;
	int nCols;
	int nRows;

	TileMap^ backgroundMap;
	Graphics^ canvas;

public:
	property int ViewportWorldX
	{
		int get()
		{
			return viewportWorldX;
		}
		void set(int v)
		{
			viewportWorldX = v;
		}
	}
	property int ViewportWorldY
	{
		int get()
		{
			return viewportWorldY;
		}
		void set(int v)
		{
			viewportWorldY = v;
		}
	}

	property int ViewportTilesWide
	{
		int get()
		{
			return viewportTilesWide;
		}
		void set(int v)
		{
			viewportTilesWide = v;
		}
	}
	property int ViewportTilesHigh
	{
		int get()
		{
			return viewportTilesHigh;
		}
		void set(int v)
		{
			viewportTilesHigh = v;
		}
	}
public:
	Viewport(int startX, int startY, int startTilesWide, int startTilesHigh, int tileWidth, int nCols, int nRows, TileMap^ startBackgroundMap, Graphics^ startCanvas);
	void ViewportMove(int xMove, int yMove);
	void ViewportDraw(TileMap^ mainTileMap);
	void FogOfWar(TileMap^ mainTileMap,int xPos,int yPos);
	void moveRelativeToPlayer(int playerWorldX, int playerWorldY);
};