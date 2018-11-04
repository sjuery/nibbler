#include "extern_ncursus.hpp"

extern "C" GameInfo* create_object()
{
	return new NCursusInfo;
}

extern "C" void destroy_object( GameInfo* object )
{
	delete object;
}

NCursusInfo::NCursusInfo()
{
	newterm(getenv("TERM"), stdout, stdin);
	raw();
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
}

NCursusInfo::~NCursusInfo()
{
	//This Sucks
}

void NCursusInfo::drawBox(struct coords crds, enum object type)
{
	(void)crds;
	(void)type;
}

int NCursusInfo::getInput()
{
	int c = getch();

	switch(c)
	{
		case '1': endwin();
			return ONE;
		case '2': endwin();
			return TWO;
		case '3': endwin();
			return THREE;
		case KEY_UP:
			return UP;
		case KEY_DOWN:
			return DOWN;
		case KEY_LEFT:
			return LEFT;
		case KEY_RIGHT:
			return RIGHT;
	}
	return '\0';
}
