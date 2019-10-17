#include "TileSet.h"
#include "Tile.h"

TileSet::TileSet(int startNTiles)
{
	tileArray = gcnew array<Tile^>(startNTiles);
}

Bitmap^ TileSet::GetTileBitmap(int tileIndex)
{
	return tileArray[tileIndex]->TileBitmap;
}

void TileSet::SetTileArrayEntry(int tileIndex, Tile^ tileToEnter)
{
	tileArray[tileIndex] = tileToEnter;
}

bool TileSet::IsTileWalkable(int tileIndex)
{
	if (tileIndex == 12)
	{
		return true;
	}
	return tileArray[tileIndex]->Walkable;
}