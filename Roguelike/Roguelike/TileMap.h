#pragma once
#include "TileSet.h"
// holds multiple tile as a set to array
ref class TileMap
{
private:
	TileSet^ tileSet;
	array<int, 2>^ map;
	Graphics^ canvas;
	int nCols;
	int nRows;

public:
	TileMap(TileSet^ startTileList, Graphics^ startCanvas, int startNcols, int startNRows);

	void SetMapEntry(int col, int row, int tileIndex);

	int GetMapEntry(int col, int row);

	void DrawMap();

	void LoadMapFromFile(String^ mapFileName);

	Bitmap^ GetMapCellBitmap(int worldRow, int worldColumn);

	bool IsWalkable(int col, int row);
};

