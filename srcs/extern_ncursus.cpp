#include "extern_ncursus.hpp"

extern "C" GameInfo* create_object( coords dimensions )
{
	(void)dimensions;
	return new NCursusInfo;
}

extern "C" void destroy_object( GameInfo* object )
{
	delete object;
}

NCursusInfo::NCursusInfo()
{
	newterm(getenv("TERM"), stdout, stdin);
	curs_set(FALSE);
	raw();
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_RED, COLOR_RED);
	init_pair(2, COLOR_GREEN, COLOR_GREEN);
	init_pair(3, COLOR_GREEN, COLOR_WHITE);
}

NCursusInfo::~NCursusInfo()
{
	endwin();
}

void NCursusInfo::display()
{
	erase();
	// refresh();
}

void NCursusInfo::drawBox(struct coords crds, enum object type)
{
	attron(COLOR_PAIR((int)type));
	mvprintw(crds.y/10, crds.x/5, "  ");
	attroff(COLOR_PAIR((int)type));
}

int NCursusInfo::getInput()
{
	int c = getch();

	switch(c)
	{
		case '1':
			return ONE;
		case '2':
			return TWO;
		case '3':
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
