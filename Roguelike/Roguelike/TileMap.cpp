#include "TileMap.h"

TileMap::TileMap(TileSet^ startTileList, Graphics^ startCanvas, int startNcols, int startNRows)
{
	tileSet = startTileList;
	canvas = startCanvas;
	map = gcnew array<int, 2>(startNcols, startNRows);
	nCols = startNcols;
	nRows = startNRows;
}

// to set each tile a number to decide which bitmap is
void TileMap::SetMapEntry(int col, int row, int tileIndex)
{
	map[col, row] = tileIndex;
}

// get the col and row of array of the tiles number
int TileMap::GetMapEntry(int col, int row)
{
	return map[col, row];
}

// check tiles walkable
bool TileMap::IsWalkable(int col, int row)
{
	if (col < nCols&&row < nRows&&col>0 && row>0)
	{
		return tileSet->IsTileWalkable(map[col, row]);
	}
	else
	{
		return false;
	}
}

// loop all of the tiles map to draw it
void TileMap::DrawMap()
{
	Bitmap^ tileBitmap = tileSet->GetTileBitmap(0);
	int width = tileBitmap->Width;
	int height = tileBitmap->Height;
	int indexCol = 0;
	int x = 0;
	do
	{
		int indexRow = 0;
		int y = 0;
		do
		{
			canvas->DrawImage((Image^)tileSet->GetTileBitmap(map[indexCol, indexRow]), x, y);
			++indexRow;
			y = height + y;
		} while (indexRow < nRows);
		++indexCol;
		x = width + x;

	} while (indexCol < nCols);
}

void TileMap::LoadMapFromFile(String^ mapFileName)
{
	// requires using namespace System::IO in the .h 
	StreamReader^ sr = File::OpenText(mapFileName);

	// Will hold each line read from the input file
	String^ currentLine = "";

	// Will hold the individual strings returned by splitting currentLine on comma
	array<String^>^ indexHolder = gcnew array<String^>(nCols);

	// Keeps track of which row of the map you are filling (one line of the file per row)
	int rowCounter = 0;

	// while loops runs until all lines have been read from the file
	while (currentLine = sr->ReadLine())
	{
		indexHolder = currentLine->Split(',');
		for (int columnCounter = 0; columnCounter < nCols; columnCounter++)
		{
			int indexValue = Convert::ToInt16(indexHolder[columnCounter]);
			map[columnCounter, rowCounter] = indexValue;
		}
		rowCounter++;
	}
}

// get the specific image from tiles location
Bitmap^ TileMap::GetMapCellBitmap(int worldRow, int worldColumn)
{
	int mapValue = map[worldRow, worldColumn];
	Bitmap^ tileImage = tileSet->GetTileBitmap(mapValue);

	return tileImage;
}