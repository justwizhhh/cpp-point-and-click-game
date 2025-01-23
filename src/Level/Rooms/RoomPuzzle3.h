
#ifndef ROOMPUZZLE3_H
#define ROOMPUZZLE3_H

#include "BaseClasses/Vector2.h"
#include "BaseClasses/Room.h"
#include "Common/RoomSwitch.h"
#include "Level/Key.h"

#include <iostream>

class RoomPuzzle3 : public Room
{
public:
	RoomPuzzle3();

	void initObjects() override;
	void initMoveAreas() override;

private:
	// Level objects
	RoomSwitch room_switch;
	Key key;
};

#endif // ROOMPUZZLE3_H