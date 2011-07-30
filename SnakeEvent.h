#ifndef SNAKE_EVENT_H
#define SNAKE_EVENT_H
#include<qevent.h>
#include<qpoint.h>
#include "RoomItem.h"
class Snake;
class SnakeEvent : public QEvent
{
public:
	SnakeEvent(Snake *snake, QPoint location, const RoomItem &r);
	~SnakeEvent();
	RoomItem getRoomItem();
	Snake *getSnake();
	QPoint getLocation();
private:
	Snake *snake;
	RoomItem item;
	QPoint location;
};
#endif
