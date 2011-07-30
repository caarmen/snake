#include "SnakeEvent.h"

SnakeEvent::SnakeEvent( Snake *snake, QPoint location, const RoomItem &r) : QEvent(QEvent::User)
{
	this->snake = snake;
	this->location = location;
	item = r;
}

SnakeEvent::~SnakeEvent()
{
}

Snake *SnakeEvent::getSnake()
{
	return snake;
}
RoomItem SnakeEvent::getRoomItem()
{
	return item;
}

QPoint SnakeEvent::getLocation()
{
	return location;
}
