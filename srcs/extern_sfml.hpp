#ifndef EXTERN_SFML_HPP
#define EXTERN_SFML_HPP
#include "extern.hpp"
#include "SFML/Graphics.hpp"

class SFMLInfo : public GameInfo {
private:
	sf::RenderWindow* _window;
public:
	SFMLInfo(coords);
	~SFMLInfo();

	int getInput();
	void drawBox(struct coords, enum object);
	void display();
};

#endif
