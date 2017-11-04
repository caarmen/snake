#ifndef SNAKE_H
#define SNAKE_H
#include<qobject.h>
#include<qlist.h>
#include<qpoint.h>
#include<qtimer.h>
#include "Room.h"
#include "Constants.h"

enum SnakeState {NotStarted, Running, Paused, Dead, Escaped};
class Room;
class SnakeListener;
class Snake : public QObject
{
public:
	Snake(Room *r, int length = 10, int speed = 1000);
	~Snake();
	int getSpeed();
	void setSpeed( int);
	int getLength();
	void setLength( int length);
	void grow( int length);
	bool isRunning();
	void addListener( SnakeListener *sListener);
	void turn( Direction);
	Direction getDirection();
	void start();
	void stop();
	void die();
	void escape();
	void timerEvent(QTimerEvent * /*unused*/);
        QList<QPoint*> *getPoints();
	SnakeState getState();
private:
	void move();
	void notifyListeners( QPoint p, RoomItem item);
        QList<QPoint*> coords;
	int speed;
	int timer;
	int growth;
	Direction direction;
	Room *room;
        QList<SnakeListener*> sListeners;
	SnakeState state;
};
#endif
