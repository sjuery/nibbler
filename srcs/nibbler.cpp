#include <dlfcn.h>
#include <iostream>
#include "extern.hpp"
#include "nibbler.hpp"

gameEntity Nibbler::newBody(char type, int x, int y)
{
	gameEntity tmpPart;

	tmpPart.type = type;
	tmpPart.coords.x = x;
	tmpPart.coords.y = y;
	return tmpPart;
}

GameInfo* Nibbler::createWindow(int input)
{
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

void Nibbler::snakeUpdate()
{
	gi->drawBox(food.coords, SNAKE);
	for(const gameEntity op : snake) {
		gi->drawBox(op.coords, SNAKE);
	}
	gi->display();
}

void Nibbler::spawnFood()
{
	food.coords.x = (rand()%51)*10;
	food.coords.y = (rand()%51)*10;
	for(const gameEntity op : snake) {
		if(op.coords.x == food.coords.x && op.coords.y == food.coords.y)
			spawnFood();
	}
}

void Nibbler::collision()
{
	for(const gameEntity op : snake) {
		if(op.type == '*')
			continue ;
		if(op.coords.x == snake.front().coords.x && op.coords.y == snake.front().coords.y)
			exit(1);
	}
	if(food.coords.x == snake.front().coords.x && food.coords.y == snake.front().coords.y)
	{
		snake.push_back(newBody('.', snake.back().coords.x, snake.back().coords.y));
		spawnFood();
	}
}

void Nibbler::controls(int input)
{
	usleep(50000);
	if(input == ONE || input == TWO || input == THREE)
	{
		delete(gi);
		gi = createWindow(input);
	}

	if((input == UP && last_input != DOWN) || (input == DOWN && last_input != UP) || (input == LEFT && last_input != RIGHT) || (input == RIGHT && last_input != LEFT))
		last_input = input;
	if(last_input == UP)
	{
		snake.front() = newBody('.', snake.front().coords.x, snake.front().coords.y);
		snake.push_front(newBody('*', snake.front().coords.x, snake.front().coords.y-10));
		snake.pop_back();
	}

	if(last_input == DOWN)
	{
		snake.front() = newBody('.', snake.front().coords.x, snake.front().coords.y);
		snake.push_front(newBody('*', snake.front().coords.x, snake.front().coords.y+10));
		snake.pop_back();
	}
	if(last_input == LEFT)
	{
		snake.front() = newBody('.', snake.front().coords.x, snake.front().coords.y);
		snake.push_front(newBody('*', snake.front().coords.x-10, snake.front().coords.y));
		snake.pop_back();
	}
	if(last_input == RIGHT)
	{
		snake.front() = newBody('.', snake.front().coords.x, snake.front().coords.y);
		snake.push_front(newBody('*', snake.front().coords.x+10, snake.front().coords.y));
		snake.pop_back();
	}
	collision();
}

void Nibbler::gameLoop(int input)
{
	int c;

	snake.push_front(newBody('*', 10, 10));
	snake.push_back(newBody('.', 10, 15));
	snake.push_back(newBody('.', 10, 20));
	snake.push_back(newBody('.', 10, 25));
	snake.push_back(newBody('.', 10, 35));
	snake.push_back(newBody('.', 10, 40));
	snake.push_back(newBody('.', 10, 45));
	snake.push_back(newBody('.', 10, 50));
	snake.push_back(newBody('.', 10, 55));
	gi = createWindow(input);
	spawnFood();
	while(1)
	{
		c = gi->getInput();
		controls(c);
		snakeUpdate();
	}
	destroy(gi);
}

int main(int argc, char** argv) {
	srand (time(NULL));
	Nibbler nibble;
	if(argc == 2)
	{
		if(atoi(argv[argc-1]) >= 1 && atoi(argv[argc-1]) <= 3)
			nibble.gameLoop(atoi(argv[argc-1]));
	}
	else
		std::cout << "Usage: ./nibbler [Display Type]" << std::endl;
}
