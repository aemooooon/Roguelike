#include "Viewport.h"

Viewport::Viewport(int startX, int startY, int startTilesWide, int startTilesHigh, int startTileWidth, int startnCols, int startnRows, TileMap^ startBackgroundMap, Graphics^ startCanvas)
{
	viewportWorldX = startX;
	viewportWorldY = startY;

	viewportTilesWide = startTilesWide;
	viewportTilesHigh = startTilesHigh;

	tileWidth = startTileWidth;
	nCols = startnCols;
	nRows = startnRows;

	backgroundMap = startBackgroundMap;
	canvas = startCanvas;

}

void Viewport::ViewportMove(int xMove, int yMove)
{
	viewportWorldX += xMove;
	if (viewportWorldX < 0)
	{
		ViewportWorldX = 0;
	}

	int num1 = nCols*tileWidth - (viewportTilesWide + 1) * tileWidth;
	if (viewportWorldX > num1)
	{

		viewportWorldX = num1;
	}

	viewportWorldY += yMove;
	if (viewportWorldY < 0)
	{
		viewportWorldY = 0;
	}

	int num2 = nRows*tileWidth - (viewportTilesHigh + 1) * tileWidth;
	if (viewportWorldY <= num2)
		return;
	viewportWorldY = num2;
}


void Viewport::FogOfWar(TileMap^ mainTileMap, int xPos, int yPos)
{
	int num1 = viewportWorldX / 32;
	int num2 = viewportWorldY / 32;
	int num3 = viewportWorldX % 32;
	int num4 = viewportWorldY % 32;

	int offer_x = Math::Abs(xPos-ViewportWorldX)/2;
	int offer_y = Math::Abs(yPos-ViewportWorldY)/2;

	for (int col = num1; col <= num1 + viewportTilesWide; ++col)
	{
		for (int row = num2; row <= num2 + viewportTilesHigh; ++row)
		{
			if(Math::Abs(xPos-col*tileWidth)<offer_x ||
				Math::Abs(yPos-row*tileWidth)<offer_y)
			{
				backgroundMap->SetMapEntry(col, row, mainTileMap->GetMapEntry(col,row));
			}
		}
	}

}


void Viewport::ViewportDraw(TileMap^ mainTileMap)
{
	int num1 = viewportWorldX / 32;
	int num2 = viewportWorldY / 32;
	int num3 = viewportWorldX % 32;
	int num4 = viewportWorldY % 32;

	for (int col = num1; col <= num1 + viewportTilesWide; ++col)
	{
		for (int row = num2; row <= num2 + viewportTilesHigh; ++row)
		{
			
			canvas->DrawImage(backgroundMap->GetMapCellBitmap(col, row), (col - num1) * tileWidth - num3, (row - num2) * tileWidth - num4);
		}
	}
}


void Viewport::moveRelativeToPlayer(int playerWorldX, int playerWorldY)
{
	viewportWorldX = playerWorldX - 400;
	if (viewportWorldX < 0)
	{
		ViewportWorldX = 0;
	}
	int num1 = nCols*tileWidth - (viewportTilesWide + 1) * tileWidth;
	if (viewportWorldX > num1)
	{

		viewportWorldX = num1;
	}
	viewportWorldY = playerWorldY - 300;
	if (viewportWorldY < 0)
	{
		viewportWorldY = 0;
	}
	int num2 = nRows*tileWidth - (viewportTilesHigh + 1) * tileWidth;
	if (viewportWorldY <= num2)
	{
		return;
	}

	viewportWorldY = num2;
}