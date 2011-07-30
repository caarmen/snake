#ifndef SNAKE_LISTENER_H
#define SNAKE_LISTENER_H
#include "SnakeEvent.h"
class SnakeListener
{
public:
	SnakeListener();
	~SnakeListener();
	virtual void receiveEvent( SnakeEvent *sEvt)=0;
};
#endif
