#include "Room.h"

Room::Room(int startX, int startY, int startW, int startH)
{
	x1 = startX;
	y1 = startY;
	w = startW;
	h = startH;

	// define far of X,Y
	x2 = x1 + w;
	y2 = y1 + h;
}

Rectangle^ Room::GetRectangle()
{
	return gcnew Rectangle(x1 - 1, y1 - 1, w + 1, h + 1); // To avoid two rooms overlap together by wall, so +/-1
}

bool Room::intersects(Room^ otherRoom)
{
	// check two rooms whether overlap
	return (x1 <= otherRoom->x2 &&
		x2 >= otherRoom->x1 &&
		y1 <= otherRoom->y2 &&
		y2 >= otherRoom->y1);
}