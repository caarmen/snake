#include "Room.h"
#include "Constants.h"
#include <qmatrix.h>
#include <qpixmap.h>
#include <qpalette.h>
#include <qpainter.h>
#include <qmessagebox.h>
#include <stdlib.h>
Room::Room() : QWidget()
{
}

Room::Room( RoomGrid grid) : QWidget(), redAppleCount(0)
{
	setFocusPolicy(Qt::StrongFocus);
	this->grid = grid;
	for(int i = 0; i < grid.width; i++)
		for(int j = 0; j < grid.height; j++)
		{
			if(grid.data[i][j] == Entrance)
			{
				entrance.setX(i);
				entrance.setY(j);
			}
			else if(grid.data[i][j] == Exit)
			{
				exit.setX(i);
				exit.setY(j);
			}
		}
	QPixmap p("images/wall.xpm");
	setFixedSize(grid.width*p.width(), grid.height*p.height());
        QPalette palette(this->palette());
        palette.setColor(QPalette::Background, QColor(0,0,0));
        this->setPalette(palette);
	populateRedApples(grid.width * grid.height / 200);
	populateGreenApples(5);
}

Room::~Room()
{
}

void Room::Room::paintEvent( QPaintEvent * /* unused */)
{
	drawRoom();
	drawSnakes();
}

void Room::keyPressEvent( QKeyEvent *kEvt)
{
	int key = kEvt->key();
        Snake *snake = snakes.at(0);
	switch(key)
	{
		case Qt::Key_Left:
                        snake->turn( West);
			break;
		case Qt::Key_Right:
                        snake->turn( East);
			break;
		case Qt::Key_Up:
                        snake->turn( North);
			break;
		case Qt::Key_Down:
                        snake->turn( South);
			break;
		case Qt::Key_Home:
                        snake->turn( NorthWest);
			break;
		case Qt::Key_PageUp:
                        snake->turn( NorthEast);
			break;
		case Qt::Key_End:
                        snake->turn( SouthWest);
			break;
		case Qt::Key_PageDown:
                        snake->turn( SouthEast);
			break;
		case Qt::Key_P:
                        if(snake->isRunning())
			{
                                snake->stop();
			}
			else
			{
                                snake->start();
			}
			break;
	}
}

void Room::timerEvent( QTimerEvent * /*unused*/)
{
}

void Room::receiveEvent( SnakeEvent *sEvt)
{
	RoomItem item = sEvt->getRoomItem();
	Snake *snake = sEvt->getSnake();
	QPoint location = sEvt->getLocation();
	int x = location.x();
	int y = location.y();
	int length = snake->getLength();
	switch(item)
	{
		case Entrance:
			timeElapsed = QTime(0,0,0);
			timeElapsed.start();
			grid.data[x][y] = Wall;
			break;
		case Wall:
			snake->die();
			QMessageBox::critical(this,"You died!", "You ran into a wall!");
			break;
		case GreenApple:
			if(length >= 10)
				snake->setLength(length - 5);
			grid.data[x][y] = Floor;
			break;
		case RedApple:
			snake->grow(5);
			grid.data[x][y] = Floor;
			redAppleCount--;
			if(!redAppleCount)
			{
				grid.data[exit.x()][exit.y()] = Exit;
			}
			break;
		case Exit:
			snake->escape();
			QMessageBox::information(this,"You won!", QString::asprintf("You ate all the red apples in %d seconds.  Congrats!", timeElapsed.elapsed() / 1000));
			break;
		case Floor:
			break;
	}
}

int Room::getWidth()
{
	return grid.width;
}

int Room::getHeight()
{
	return grid.height;
}

void Room::addSnake( Snake *snake)
{
	snake->addListener(this);
        snakes.append(snake);
}

void Room::removeSnake( Snake *snake)
{
        snakes.removeOne(snake);
}

RoomItem Room::getRoomItem( int x, int y)
{
	return grid.data[x][y];
}

QPoint Room::getEntrance()
{
	return entrance;
}


QPoint Room::getExit()
{
	return exit;
}

void Room::setRoomItem( int x, int y, RoomItem i)
{
	if(x <= grid.width && y <= grid.height)
		grid.data[x][y] = i;
}	

void Room::drawRoom()
{

	QPainter paint(this);
	QPixmap wallPix("images/wall.xpm");
	QPixmap greenApplePix("images/greenApple.xpm");
	QPixmap redApplePix("images/redApple.xpm");
	int pw = wallPix.width();
	int ph = wallPix.height();
	for(int i = 0; i < grid.width; i++)
	{

		for(int j = 0; j < grid.height; j++)
		{
			switch(grid.data[i][j])
			{
			case Wall:
				paint.drawPixmap(i*pw, j*ph, wallPix);
				break;
			case RedApple:
				paint.drawPixmap(i*pw, j*ph, redApplePix);
				break;
			case GreenApple:
				paint.drawPixmap(i*pw, j*ph, greenApplePix);
				break;
			case Exit:
				if(redAppleCount > 0)
					paint.drawPixmap(i*pw, j*ph, wallPix);
				break;
			default:
				break;
			}

		}
	}
}

void Room::drawSnakes()
{
	QPainter paint(this);
	QPixmap snakePix("images/snake.xpm");
	QPixmap snakeHead("images/head.xpm");
	int pw = snakePix.width();
	int ph = snakePix.height();
	for( int i = 0; i < snakes.count(); i++)
	{
                Snake *snake = snakes.at( i);
                Direction dir = snake->getDirection();
                QMatrix m;
		switch(dir)
		{
		case NorthEast:
			m.rotate(45);
			break;
		case East:
			m.rotate(90);
			break;
		case SouthEast:
			m.rotate(135);
			break;
		case South:
			m.rotate(180);
			break;
		case SouthWest:
			m.rotate(225);
			break;
		case West:
			m.rotate(270);
			break;
		case NorthWest:
			m.rotate(315);
			break;
		default:
			break;
		}

                QList<QPoint*> *points = snake->getPoints();
		QPoint *head = points->at(0);
                snakeHead = snakeHead.transformed( m);
		paint.drawPixmap(pw*head->x(), ph*head->y(), snakeHead);
		for( int j = 1; j < points->count(); j++)
		{
			QPoint *p = points->at(j);
			paint.drawPixmap(pw*p->x(), ph*p->y(), snakePix);
		}
	}
}

void Room::populateGreenApples( int n)
{
	for(int i = 0; i < n; i++)
	{
		int x = random() % (grid.width - 2) + 1;
		int y = random() % (grid.height - 2) + 1;
		if(grid.data[x][y] == Floor)
			grid.data[x][y] = GreenApple;
	}
}

void Room::populateRedApples( int n)
{
	for(int i = 0; i < n; i++)
	{
		int x = random() % (grid.width - 2) + 1;
		int y = random() % (grid.height - 2) + 1;
		if(grid.data[x][y] == Floor)
		{
			redAppleCount++;
			grid.data[x][y] = RedApple;
		}
	}
}

void Room::focusInEvent(QFocusEvent *event)
{

        Snake *snake = snakes.at(0);
	if(snake->getState() == NotStarted || snake->getState() == Paused)
		snake->start();
	QWidget::focusInEvent(event);
}

void Room::focusOutEvent(QFocusEvent *event)
{
        Snake *snake = snakes.at(0);
	if(snake->isRunning())
		snake->stop();
	QWidget::focusOutEvent(event);
}

