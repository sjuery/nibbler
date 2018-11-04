#include <dlfcn.h>
#include <iostream>
#include "extern.hpp"
#include "nibbler.hpp"

GameInfo* Nibbler::createWindow(int input)
{
	std::cout << "Test" << std::endl;
	void* handle = nullptr;

	if(input == 1)
		if(!(handle = dlopen("extern_sfml.dylib", RTLD_LAZY)))
			return NULL;
	if(input == 2)
		if(!(handle = dlopen("extern_ncursus.dylib", RTLD_LAZY)))
			return NULL;
	if(input == 3)
		if(!(handle = dlopen("extern_opengl.dylib", RTLD_LAZY)))
			return NULL;

	create = (GameInfo* (*)())dlsym(handle, "create_object");
	destroy = (void (*)(GameInfo*))dlsym(handle, "destroy_object");
	return((GameInfo*)create());
}

void Nibbler::playerController(int input)
{
	if(input == UP)
		snake->crds.y++;
	if(input == DOWN)
		snake->crds.y--;
	if(input == LEFT)
		snake->crds.x--;
	if(input == RIGHT)
		snake->crds.x++;
}

void Nibbler::draw()
{
	gi->drawBox(snake->crds, SNAKE);
}

void Nibbler::gameLoop(int input)
{
	int c;

	snake = new snakeList();
	gi = createWindow(input);
	while(1)
	{
		c = gi->getInput();
		playerController(c);
		draw();
		if(c >= 1 && c <= 3)
		{
			gi = createWindow(c);
		}
	}
	destroy( gi );
}

int main(int argc, char** argv) {
	Nibbler nibble;
	if(argc == 2)
	{
		if(atoi(argv[argc-1]) >= 1 && atoi(argv[argc-1]) <= 3)
			nibble.gameLoop(atoi(argv[argc-1]));
	}
	else
		std::cout << "Usage: ./nibbler [Display Type]" << std::endl;
}
