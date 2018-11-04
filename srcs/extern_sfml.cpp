#include "extern_sfml.hpp"

extern "C" GameInfo* create_object()
{
	return new SFMLInfo();
}

extern "C" void destroy_object( GameInfo* object )
{
	delete object;
}

SFMLInfo::SFMLInfo()
{
	_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Test");
}

SFMLInfo::~SFMLInfo()
{
	//This Sucks
}

void SFMLInfo::drawBox(struct coords crds, enum object type)
{
	(void)crds;
	(void)type;
}

int SFMLInfo::getInput()
{
	if(_window->isOpen())
	{
		sf::Event event;
		while (_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				_window->close();
				delete _window;
				exit(1);
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Num1)
				{
					_window->close();
					delete _window;
					return ONE;
				}
				if (event.key.code == sf::Keyboard::Num2)
				{
					_window->close();
					delete _window;
					return TWO;
				}
				if (event.key.code == sf::Keyboard::Num3)
				{
					_window->close();
					delete _window;
					return THREE;
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					return UP;
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					return DOWN;
				}
				if (event.key.code == sf::Keyboard::Left)
				{
					return LEFT;
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					return RIGHT;
				}
			}
		}
	}
	return '0';
}
