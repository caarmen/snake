#ifndef ROOM_ITEM_H
#define ROOM_ITEM_H
enum RoomItem { Wall, GreenApple, RedApple, Entrance, Exit, Floor};
struct RoomGrid
{
	RoomItem **data;
	int width;
	int height;
};
#endif
