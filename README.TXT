Snake game
Carmen Alvarez

This is a game I wrote in April 2001, in part to pass the time away, in part
out of curiosity to learn QT. 

REQUIREMENTS
This game was initially written for Qt on Linux in 2001.  In June 2011, I
updated it to compile on the latest version of Qt (4.7) on Mac OS X. I updated
it again in November 2017 to compile with Qt 5.9.2 on Mac OS X.

BUILDING
These steps have only been tested on Mac OS X:
* qmake -project
* qmake QT+=widgets
* make

RUNNING 
Run the snake executable.
Optional argument: --file <filename> where <filename> is a snake level
file.  

PLAYING THE GAME
The goal is to collect all the red apples and exit the game, in the fastest
time possible.  Eating a red apple increases the snake's length, and 
eating a green apple shortens the snake.


SNAKE LEVEL FILES 
You can create custom levels. The level is drawn in ASCII in a text file,
and specified with the --file argument when running the game. 

The first two lines of the file must start with a number which indicates 
the width and height, respectively.

* Place 'W' characters where the walls should appear.
* Place an 'N' character where the snake should enter the game.  This should
be on one of the borders (top, left, right, bottom) of the room.
* Place an 'X' character where the snake should exit the game. The exit
will appear as a wall throughout the game, and after collecting all the
red apples, the exit will transform into a black tile.
For this reason, it is recommended to place the exit
either on one of the borders, or in the middle of one of the walls.


