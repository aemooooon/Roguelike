#pragma once
#include "Tile.h"
// holds a collection fo tiles to 2 D array
ref class TileSet
{
private:
	array<Tile^>^ tileArray;
	int nTiles;
public:
	TileSet(int startNTiles);

	Bitmap^ GetTileBitmap(int tileIndex);

	void SetTileArrayEntry(int tileIndex, Tile^ tileToEnter);

	bool IsTileWalkable(int tileIndex);
};

