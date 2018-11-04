#ifndef EXTERN_NCURSUS_HPP
#define EXTERN_NCURSUS_HPP
#include "extern.hpp"
#include <ncurses.h>

class NCursusInfo : public GameInfo {
public:
	NCursusInfo();
	~NCursusInfo();

	int getInput();
	void drawBox(struct coords, enum object);
};

#endif
