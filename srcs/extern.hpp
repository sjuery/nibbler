#ifndef EXTERN_HPP
#define EXTERN_HPP
#include <iostream>
#include <unistd.h>

enum object {
	SNAKE = 1,
	FOOD,
	WALL
};

enum keys {
	ONE = 1,
	TWO,
	THREE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct coords {
	int x;
	int y;
};

class GameInfo {
public:
	GameInfo() {};
	virtual ~GameInfo() {};

	virtual int getInput() = 0;
	virtual void drawBox(struct coords, enum object) = 0;
	virtual void display() = 0;
};

#endif
