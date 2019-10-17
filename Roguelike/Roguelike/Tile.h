#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;

ref class Tile
{
private:
	Bitmap^ tileBitmap;
	bool walkable;
public:
	property Bitmap^ TileBitmap
	{
		Bitmap^ get()
		{
			return tileBitmap;
		}
		void set(Bitmap^ b)
		{
			tileBitmap = b;
		}
	}
	property bool Walkable // Give a flag to make a tile whether walkable
	{
		bool get()
		{
			return walkable;
		}
		void set(bool b)
		{
			walkable = b;
		}
	}
public:
	Tile(Bitmap^ startTileBitmap, bool startWalkable);
};

