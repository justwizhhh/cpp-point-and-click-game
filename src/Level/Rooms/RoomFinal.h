
#ifndef ROOMFINAL_H
#define ROOMFINAL_H

#include "BaseClasses/Vector2.h"
#include "BaseClasses/Room.h"
#include "Common/RoomSwitch.h"
#include "Level/Coffin.h"

#include <iostream>

class RoomFinal : public Room
{
public:
	RoomFinal();

	void initObjects() override;
	void initMoveAreas() override;

private:
	// Level objects
	RoomSwitch room_switch;
	Coffin coffin;
};

#endif // ROOMFINAL_H