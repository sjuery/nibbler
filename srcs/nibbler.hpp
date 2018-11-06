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
	GameInfo* gi;
	GameInfo* (*create)();
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
	void gameLoop(int);
};

#endif
