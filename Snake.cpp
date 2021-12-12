#include "Snake.h"
#include <qmessagebox.h>

Snake::Snake( Room *r, int length, int speed)
{
	room = r;
	QPoint entrance = r->getEntrance();
	int xEntrance = entrance.x();
	int yEntrance = entrance.y();
	int width = r->getWidth();
	int height = r->getHeight();
	if(xEntrance == 0)
	{
		coords.append( new QPoint( 0, yEntrance));
		coords.append( new QPoint( -1, yEntrance));
		direction = East;
	}
	else if(xEntrance == width - 1)
	{
		coords.append( new QPoint( width, yEntrance));
		coords.append( new QPoint( width + 1, yEntrance));
		direction = West;
	}
	else if(yEntrance == 0)
	{
		coords.append( new QPoint( xEntrance, 0));
		coords.append( new QPoint( xEntrance, -1));
		direction = South;
	}
	else if(yEntrance == height -1)
	{
		coords.append( new QPoint( xEntrance, height));
		coords.append( new QPoint( xEntrance, height + 1));
		direction = North;
	}
	setLength(length - 2);
	state = NotStarted;
	setSpeed( speed);
	r->addSnake(this);
	growth = 0;
}

Snake::~Snake()
{
}

int Snake::getSpeed()
{
	return speed;
}
void Snake::setSpeed( int s)
{
	speed = s;
	if( isRunning())
	{
		stop();
		start();
	}
}

int Snake::getLength()
{
	return coords.count();
}
void Snake::setLength( int length)
{
	int size = coords.count();
	if( length <  size)
	{
                for(int i=length; i < size; i++)
                    coords.removeLast();
	}
	else
	{
		for(int i=size; i<length; i++)
		{
			size = coords.count();
			QPoint *p = coords.at( size - 1);
			QPoint *prev = coords.at(size - 2);
			int newX = p->x() + (p->x() - prev->x());
			int newY = p->y() + (p->y() - prev->y());
			QPoint *newPoint = new QPoint( newX, newY);
			coords.append( newPoint);
		}
	}

}

void Snake::grow( int length)
{
	growth = length;
}
bool Snake::isRunning()
{
	return (state == Running);
}
void Snake::addListener( SnakeListener *sListener)
{
	sListeners.append( sListener);
}
void Snake::turn( Direction dir)
{
	int change = dir - direction;
	if(change == 4 || change == -4)
		return;
	direction = dir;
	move();
}

Direction Snake::getDirection()
{
	return direction;
}

void Snake::start()
{
	if(state == Dead || state == Escaped)
		return;
	state = Running;
	timer = startTimer(speed);
	QPoint *head = coords.first();
	notifyListeners(*head,room->getRoomItem(head->x(),head->y()));
}
void Snake::stop()
{
	if(state == Dead || state == Escaped)
		return;
	state = Paused;
	killTimer( timer);
}
void Snake::die()
{
	stop();
	state = Dead;
}
void Snake::escape()
{
	stop();
	state = Escaped;
}
void Snake::timerEvent(QTimerEvent * /*unused*/)
{
	move();
}

QList<QPoint*> *Snake::getPoints()
{
	return &coords;
}
void Snake::move()
{
	QPoint *head = coords.at(0);
	int x = head->x();
	int y = head->y();
	switch( direction)
	{
	case North:
		y = head->y()-1;
		break;
	case NorthEast:
		x = head->x()+1;
		y = head->y()-1;
		break;
	case East:
		x = head->x()+1;
		break;
	case SouthEast:
		x = head->x()+1;
		y = head->y()+1;
		break;
	case South:
		y = head->y()+1;
		break;
	case SouthWest:
		x = head->x()-1;
		y = head->y()+1;
		break;
	case West:
		x = head->x()-1;
		break;
	case NorthWest:
		x = head->x()-1;
		y = head->y()-1;
		break;
	}

	for(int i = coords.count() - 1; i>0; i--)
	{
		QPoint *p = coords.at(i);
		QPoint *prev = coords.at(i-1);

		if(p->x() == x  && p->y() == y )
		{
			die();
			QMessageBox::critical(room, "You died!", "You ran into yourself!");
			return;
		}
		p->setX(prev->x());
		p->setY(prev->y());
	}
	head->setX(x);
	head->setY(y);
	room->repaint();
	RoomItem item = room->getRoomItem( head->x(), head->y());

	if(item != Floor)
		notifyListeners( *head, item);
	if(growth >0)
	{
		setLength(coords.count() + 1);
		growth--;
	}
}
void Snake::notifyListeners( QPoint p, RoomItem item)
{
    for(int i=0; i < sListeners.size(); i++)
    {
        SnakeListener *s = sListeners.at(i);
	SnakeEvent sEvt(this, p, item);
        s->receiveEvent( &sEvt);
    }
}
SnakeState Snake::getState()
{
	return state;
}
