#include "extern_sfml.hpp"

extern "C" GameInfo* create_object( coords dimensions )
{
	return new SFMLInfo(dimensions);
}

extern "C" void destroy_object( GameInfo* object )
{
	delete object;
}

SFMLInfo::SFMLInfo(coords dimensions)
{
	_window = new sf::RenderWindow(sf::VideoMode(dimensions.x*10, dimensions.y*10), "Test");
}

SFMLInfo::~SFMLInfo()
{
	_window->close();
	delete _window;
}

void SFMLInfo::display()
{
	//
	_window->display();
	_window->clear(sf::Color::Black);
}

void SFMLInfo::drawBox(struct coords crds, enum object type)
{
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(1, 1));
	rectangle.setOutlineThickness(5);
	rectangle.setPosition(crds.x, crds.y);
	_window->draw(rectangle);

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
					return ONE;
				if (event.key.code == sf::Keyboard::Num2)
					return TWO;
				if (event.key.code == sf::Keyboard::Num3)
					return THREE;
				if (event.key.code == sf::Keyboard::Up)
					return UP;
				if (event.key.code == sf::Keyboard::Down)
					return DOWN;
				if (event.key.code == sf::Keyboard::Left)
					return LEFT;
				if (event.key.code == sf::Keyboard::Right)
					return RIGHT;
			}
		}
	}
	return '0';
}
