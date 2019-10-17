#include "Dungeon.h"
#define ROOM_SIZE_MIN 7
#define ROOM_SIZE_MAX 20

Dungeon::Dungeon(TileMap^ startTileMap, int startMapCols, int startMapRows, int startNTiles, int startRooms, Random^ startRGen)
{
	tileMap = startTileMap;
	mapCols = startMapCols;
	mapRows = startMapRows;
	nTiles = startNTiles;
	nRooms = startRooms;
	rGen = startRGen;
	rooms = gcnew List<Room^>();
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ClearDungeon method change all tiles to 1, make backgroud
///////////////////////////////////////////////////////////////////////////////////////////////
void Dungeon::ClearDungeon()
{
	for (int i = 0; i < mapCols; i++)
	{
		for (int j = 0; j < mapRows; j++)
		{
			int tileIndex = 3;
			tileMap->SetMapEntry(i, j, tileIndex);
		}
	}
}

List<Room^>^ Dungeon::GetRooms()
{
	return rooms;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Return the first rooms centre points
///////////////////////////////////////////////////////////////////////////////////////////////
Point^ Dungeon::GetRndRoomXY()
{
	Point^ result = gcnew Point();

	result->X = rooms[0]->Centre_X;
	result->Y = rooms[0]->Centre_Y;

	return result;
}

void Dungeon::MakeNewDungeon()
{

	int roomW;
	int roomH;
	int roomX;
	int roomY;

	int z = 0;
	while (z < nRooms)
	{
		int roomW = rGen->Next(ROOM_SIZE_MIN, ROOM_SIZE_MAX);
		int roomH = rGen->Next(ROOM_SIZE_MIN, ROOM_SIZE_MAX);
		int roomX = rGen->Next(30, mapCols - roomW - 30);
		int roomY = rGen->Next(20, mapRows - roomH - 20);

		Room^ room = gcnew Room(roomX, roomY, roomW, roomH);

		// Check the new rooms border whether intersects with already have rooms
		bool failed = false;
		for (int i = 0; i < rooms->Count; i++)
		{
			if (rooms[i]->GetRectangle()->IntersectsWith((Rectangle)room->GetRectangle()))
			{
				failed = true;
				break;
			}
		}

		if (!failed)
		{
			// if not intersects with given rooms and Add new room to List
			Room^ newRoom = gcnew Room(roomX, roomY, roomW, roomH);
			rooms->Add(newRoom);

			// fill tiles type to map
			for (int i = 0; i < newRoom->W; i++)
			{
				for (int j = 0; j < newRoom->H; j++)
				{
					int tileIndex = 0;
					// set corridor tiles style
					if (i == 0 ||
						j == 0 ||
						i == newRoom->W - 1 ||
						j == newRoom->H - 1
						)
					{
						tileIndex = 2;
					}
					tileMap->SetMapEntry(i + newRoom->X1, j + newRoom->Y1, tileIndex);
				}
			}
			z++;
		}

	}

	// this for loop just make all corridor between two rooms
	// from one rooms to another connect to centre
	// each verticly and horizontal has 50% chance to draw
	for (int i = 1; i < rooms->Count; i++)
	{
		int flipCoin = rGen->Next(2);
		int prevCentreX = rooms[i - 1]->Centre_X;
		int prevCentreY = rooms[i - 1]->Centre_Y;
		int currCentreX = rooms[i]->Centre_X;
		int currCentreY = rooms[i]->Centre_Y;
		// put this coin flag 
		if (flipCoin == 1)
		{
			for (int x = Math::Min(prevCentreX, currCentreX); x <= Math::Max(prevCentreX, currCentreX); x++)
			{
				int tileIndex = 0;
				tileMap->SetMapEntry(x, prevCentreY, tileIndex);
			}

			for (int y = Math::Min(prevCentreY, currCentreY); y <= Math::Max(prevCentreY, currCentreY); y++)
			{
				int tileIndex = 0;
				tileMap->SetMapEntry(currCentreX, y, tileIndex);
			}
		}
		else
		{
			for (int y = Math::Min(prevCentreY, currCentreY); y <= Math::Max(prevCentreY, currCentreY); y++)
			{
				int tileIndex = 0;
				tileMap->SetMapEntry(currCentreX, y, tileIndex);
			}

			for (int x = Math::Min(prevCentreX, currCentreX); x <= Math::Max(prevCentreX, currCentreX); x++)
			{
				int tileIndex = 0;
				tileMap->SetMapEntry(x, prevCentreY, tileIndex);
			}
		}
	}
}
