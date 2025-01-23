
#ifndef ROOMPUZZLE1_H
#define ROOMPUZZLE1_H

#include "BaseClasses/Vector2.h"
#include "BaseClasses/Room.h"
#include "Level/Key.h"
#include "Level/Vase.h"
#include "Common/RoomSwitch.h"

#include <iostream>

class RoomPuzzle1 : public Room
{
public:
	RoomPuzzle1();

	void initText() override;
	void initObjects() override;
	void initMoveAreas() override;

private:
	// Level objects
	RoomSwitch room_switch;

	Vase empty_vase1;
	Vase empty_vase2;
	Vase empty_vase3;
	Vase key_vase;
	Key key;

	// Text
	sf::Font font;

	sf::Text text_1;
	sf::Text text_2;
};

#endif // ROOMPUZZLE1_H