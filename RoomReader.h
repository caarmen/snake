#ifndef ROOMREADER_H
#define ROOMREADER_H
#include "RoomItem.h"
class RoomReader
{
public:
	RoomReader();
	static RoomGrid readFile(const char *filename);
};
#endif
