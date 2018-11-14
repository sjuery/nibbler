#include <dlfcn.h>
#include <iostream>
#include "extern.hpp"
#include "nibbler.hpp"
#include <sys/time.h>

unsigned getTickCount()
{
	struct timeval tv;
    gettimeofday(&tv, 0);
    return unsigned((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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

	create = (GameInfo* (*)(coords))dlsym(handle, "create_object");
	destroy = (void (*)(GameInfo*))dlsym(handle, "destroy_object");
	return((GameInfo*)create(dimensions));
}

void Nibbler::snakeUpdate()
{
	coords tmpCoords;
	gi->display();
	for(int y = 1; y < dimensions.y * 10; y++)
	{
		tmpCoords.x = 0;
		tmpCoords.y = y;
		gi->drawBox(tmpCoords, WALL);
		tmpCoords.x = dimensions.x*10;
		gi->drawBox(tmpCoords, WALL);
	}
	for(int x = 1; x < dimensions.x * 10; x++)
	{
		tmpCoords.x = x;
		tmpCoords.y = 0;
		gi->drawBox(tmpCoords, WALL);
		tmpCoords.y = dimensions.y*10;
		gi->drawBox(tmpCoords, WALL);
	}
	gi->drawBox(food.coords, FOOD);
	for(const gameEntity op : snake) {
		gi->drawBox(op.coords, SNAKE);
	}
}

void Nibbler::spawnFood()
{
	food.coords.x = (rand()%(dimensions.x-1)+1)*10;
	food.coords.y = (rand()%(dimensions.y-1)+1)*10;
	for(const gameEntity op : snake) {
		if(op.coords.x == food.coords.x && op.coords.y == food.coords.y)
			spawnFood();
	}
}

void Nibbler::collision()
{
	coords tmpCoords;
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
	for(int y = 1; y < dimensions.y * 10; y++)
	{
		tmpCoords.x = 0;
		tmpCoords.y = y;
		if(tmpCoords.x == snake.front().coords.x && tmpCoords.y == snake.front().coords.y)
			exit(1);
		tmpCoords.x = dimensions.x*10;
		if(tmpCoords.x == snake.front().coords.x && tmpCoords.y == snake.front().coords.y)
			exit(1);
	}
	for(int x = 1; x < dimensions.x * 10; x++)
	{
		tmpCoords.x = x;
		tmpCoords.y = 0;
		if(tmpCoords.x == snake.front().coords.x && tmpCoords.y == snake.front().coords.y)
			exit(1);
		tmpCoords.y = dimensions.y*10;
		if(tmpCoords.x == snake.front().coords.x && tmpCoords.y == snake.front().coords.y)
			exit(1);
	}
}

void Nibbler::controls(int input)
{
	if(input == ONE || input == TWO || input == THREE)
	{
		delete(gi);
		gi = createWindow(input);
	}
	collision();
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
}

void Nibbler::gameLoop(int x, int y)
{
	int c;

	dimensions.x = x;
	dimensions.y = y;
	int loops;
	float next_game_tick = getTickCount();
	snake.push_front(newBody('*', dimensions.x*10/2, dimensions.y*10/2));
	snake.push_back(newBody('.', dimensions.x*10/2, dimensions.y*10/2+5));
	snake.push_back(newBody('.', dimensions.x*10/2, dimensions.y*10/2+10));
	snake.push_back(newBody('.', dimensions.x*10/2, dimensions.y*10/2+15));
	gi = createWindow(3);
	spawnFood();
	while(1)
	{
		loops = 0;
		while(getTickCount() > next_game_tick && loops < 1)
		{
			controls(c);
			c = gi->getInput();
			next_game_tick += 120 + 1000/next_game_tick;
			loops++;
		}
		snakeUpdate();
	}
	destroy(gi);
}

int main(int argc, char** argv) {
	srand (time(NULL));
	Nibbler nibble;
	if(argc == 3)
	{
		nibble.gameLoop(atoi(argv[argc-2]), atoi(argv[argc-1]));
	}
	else
		std::cout << "Usage: ./nibbler [Display Type]" << std::endl;
}
