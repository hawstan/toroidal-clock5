#include <QGuiApplication>
#include <unistd.h>

#include "ToroidalClock5.h"

#define HELP_TEXT "  ToroidialClock5\n"\
	"==========\n"\
	"Version 0.1\n"\
	"Displays time using text surrounded by arcs to represent hours, minutes, seconds.\n"\
	"Created 2013-08-17 by Stanley Hawkeye.\n"\
	"Licensed under The MIT License.\n"\
	"\n Arguments:\n"\
	"  -x <num>    X position of the window\n"\
	"  -y <num>    Y position of the window\n"\
	"  -h          this help message\n"\
	"\n"

int main(int argc, char *argv[])
{
	int x = 0;
	int y = 0;

	QGuiApplication app(argc, argv);
	//TODO change this to QOptionParser after it's ready
	int c;
	while( (c = getopt(argc, argv, "x:y:h")) != -1)
	{
		switch(c)
		{
			case 'x':
				x = QString(optarg).toInt();
				break;

			case 'y':
				y = QString(optarg).toInt();
				break;

			case 'h':
				printf(HELP_TEXT);
				return 0;

			default:
				printf("Found unrecognised option, try \"toroidial-clock5 -h\"\n");
				break;
		}
	}

	ToroidalClock5 window;
	window.setPosition(x, y);
	window.show();
	return app.exec();
}
