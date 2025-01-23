
#ifndef ROOMEND_H
#define ROOMEND_H

#include "BaseClasses/Vector2.h"
#include "BaseClasses/Room.h"

#include <iostream>

class RoomEnd : public Room
{
public:
	RoomEnd();

	void initText() override;

private:
	// Text
	sf::Font font;

	sf::Text text_1;
	sf::Text text_2;
};

#endif // ROOMEND_H