#ifndef NIBBLER_HPP
#define NIBBLER_HPP
#include <iostream>
#include <list>
#include <unistd.h>

#define SNAKESIZE 5;

struct gameEntity
{
	char type;
	struct coords coords;
};

class Nibbler {
private:
	struct coords dimensions;
	GameInfo* gi;
	GameInfo* (*create)(coords);
	void (*destroy)(GameInfo*);
	int last_input;
	std::list<gameEntity> snake;
	gameEntity food;

public:
	Nibbler() {};
	virtual ~Nibbler() {};

	gameEntity newBody(char, int, int);
	GameInfo* createWindow(int);
	void spawnFood();
	void controls(int);
	void collision();
	void snakeUpdate();
	void gameLoop(int, int);
};

#endif
