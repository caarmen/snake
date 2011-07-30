#include "RoomReader.h"
#include<qfile.h>
#include<qstring.h>
#include<qtextstream.h>
RoomReader::RoomReader()
{
}

RoomGrid RoomReader::readFile(const char *filename)
{
	RoomGrid grid;
	grid.height = 0;
	grid.width = 0;
	grid.data = 0;
	QFile f(filename);
        if(!f.open(QIODevice::ReadOnly))
	{
		printf("Couldn't open file %s\n", filename);
		return grid;
	}
	QTextStream t(&f);
	QString s;
	//Get room dimensions
	s = t.readLine();
	int width = s.toInt();
	s = t.readLine();
	int height = s.toInt();
	RoomItem **roomGrid = (RoomItem**) malloc(width*sizeof(RoomItem*));
	grid.width = width;
	grid.height = height;
	grid.data = roomGrid;
	int i,j;
	for(i=0; i<width; i++)
		roomGrid[i] = (RoomItem*) malloc(height*sizeof(RoomItem));
        for(j=0; j<height/* && !t.eof()*/; j++)
	{
		s = t.readLine();
                if(s.isNull())
                    break;
		for(i=0; i<s.length() && i < width; i++)
		{
                        char c =  s.at(i).toLatin1();
			switch(c)
			{
				case 'W':
					roomGrid[i][j] = Wall;
					break;
				case 'N':
					roomGrid[i][j] = Entrance;
					break;
				case 'X':
					roomGrid[i][j] = Exit;
					break;
				default:
					roomGrid[i][j] = Floor;
					break;
			}
			if((i == 0 || i == (width- 1) || j == 0 || j == (height- 1)) && roomGrid[i][j] == Floor)
				roomGrid[i][j] = Wall;
		}
		for(;i<width;i++)
		{
			if(i == 0 || i == (width- 1) || j == 0 || j == (height- 1))
				roomGrid[i][j] = Wall;
			else
				roomGrid[i][j] = Floor;

		}
	}
	for(;j<height;j++)
	{
		for(i=0; i<width; i++)
		{
			if(i == 0 || i == (width - 1) || j == 0 || j == (height - 1))
				roomGrid[i][j] = Wall;
			else
				roomGrid[i][j] = Floor;
		}
	}
	return grid;
}

