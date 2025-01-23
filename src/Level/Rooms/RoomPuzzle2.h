
#ifndef ROOMPUZZLE2_H
#define ROOMPUZZLE2_H

#include "BaseClasses/Vector2.h"
#include "BaseClasses/Room.h"
#include "Common/RoomSwitch.h"
#include "Level/Crank.h"
#include "Level/Key.h"
#include "Level/KeyContainer.h"

#include <iostream>

class RoomPuzzle2 : public Room
{
public:
	RoomPuzzle2();

	void initObjects() override;
	void initMoveAreas() override;

private:
	// Level objects
	RoomSwitch room_switch;
	Key key;
	KeyContainer key_container;
	Crank crank;
};

#endif // ROOMPUZZLE2_H