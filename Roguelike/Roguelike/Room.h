#pragma once
using namespace System::Drawing;

///////////////////////////////////////////////////////////////////////////////////////////////
// Single room Class 
// holds X,Y,W,H,Far of X,Y and Centre of X,Y
// get rooms as rectangle method reture a rectangle
// Intersects method check whether intersects with other rooms
///////////////////////////////////////////////////////////////////////////////////////////////

ref class Room
{
private:
	int x1;
	int y1;
	int x2;
	int y2;
	int w;
	int h;
public:
	property int Centre_X
	{
		int get()
		{
			int temp = (x1 + x2) / 2;
			return temp;
		}
	}

	property int Centre_Y
	{
		int get()
		{
			int temp = (y1 + y2) / 2;
			return temp;
		}
	}

	property int X1
	{
		int get()
		{
			return x1;
		}
	}
	property int Y1
	{
		int get()
		{
			return y1;
		}
	}
	property int X2
	{
		int get()
		{
			return x2;
		}
	}
	property int Y2
	{
		int get()
		{
			return y2;
		}
	}
	property int W
	{
		int get()
		{
			return w;
		}
	}
	property int H
	{
		int get()
		{
			return h;
		}
	}
public:
	Room(int x, int y, int w, int h);
	Rectangle^ GetRectangle();
	bool intersects(Room^ otherRoom);
};

