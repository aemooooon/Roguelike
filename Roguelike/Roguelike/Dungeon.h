#pragma once
#include "TileMap.h"
#include "Room.h"

using namespace System::Collections::Generic;

ref class Dungeon
{
private:
	int nRooms;
	TileMap^ tileMap;
	int mapCols;
	int mapRows;
	int nTiles;
	Random^ rGen;
	List<Room^>^ rooms; // A collections of room

public:
	Dungeon(TileMap^ tileMap, int mapCols, int mapRows, int nTiles, int nRooms, Random^ rGen);
	void ClearDungeon(); // Put all tiles to single style - backgroud
	void MakeNewDungeon(); // Generate Dungeon map
	Point^ GetRndRoomXY(); // Return singel rooms Centre X, Y of Point
	List<Room^>^ GetRooms(); // Reurn all rooms
};

