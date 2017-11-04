#ifndef ROOM_H
#define ROOM_H

#include <qdatetime.h>
#include <qmainwindow.h>
#include <qwidget.h>
#include <qlist.h>
#include <qpoint.h>
#include "RoomItem.h"
#include "SnakeListener.h"
#include "Snake.h"
#include "SnakeEvent.h"

class SnakeListener;

class Room : public SnakeListener, public QWidget
{

public:
	Room();
	Room(RoomGrid grid);
	~Room();
	void paintEvent( QPaintEvent * /*unused*/);
	void keyPressEvent( QKeyEvent *kEvt);
	void timerEvent( QTimerEvent * /*unused*/);
	void receiveEvent( SnakeEvent *sEvt);
	int getWidth();
	int getHeight();
	void addSnake( Snake *snake);
	void removeSnake( Snake *snake);
	RoomItem getRoomItem( int x, int y);
	QPoint getEntrance();
	QPoint getExit();
	void focusInEvent(QFocusEvent *event);
	void focusOutEvent(QFocusEvent *event);
private:
	void setRoomItem( int x, int y, RoomItem i);
	void drawRoom(); 
	void drawSnakes();
	void populateGreenApples( int n);
	void populateRedApples( int n);
	RoomGrid grid;
	QPoint entrance;
	QPoint exit;
        QList<Snake * > snakes;
	int redAppleCount;
	QTime timeElapsed;
};
#endif
