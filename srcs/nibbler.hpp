#ifndef NIBBLER_HPP
#define NIBBLER_HPP
#include <iostream>
#include <unistd.h>

struct snakeList {
	coords crds;
	struct snakeList *prev;
	struct snakeList *next;
};

class Nibbler {
private:
	GameInfo* gi;
	GameInfo* (*create)();
	void (*destroy)(GameInfo*);
	snakeList *snake;
public:
	Nibbler() {};
	virtual ~Nibbler() {};

	GameInfo* createWindow(int);
	void playerController(int);
	void draw();
	void gameLoop(int);
};

#endif
