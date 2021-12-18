#include "Snake.h"
#include "Room.h"
#include "RoomReader.h"
#include <qapplication.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
	const char *filename = ":/level1.snl";
	srandom(time(NULL));
	for(int i=0; i<argc; i++)
	{
		if(!(strcmp(argv[i],"--file")) || !(strcmp(argv[i],"-f")))
			filename = argv[++i];
	}
	RoomGrid grid = RoomReader::readFile(filename);
	QApplication app( argc, argv);
	Room r(grid);
        Snake s(&r, 5, 200);
        r.show();
        return app.exec();
}

