
#ifndef ROOMENTRANCE_H
#define ROOMENTRANCE_H

#include "BaseClasses/Room.h"
#include "Common/RoomSwitch.h"

class RoomEntrance : public Room
{
	public:
		RoomEntrance();
			
		void initText() override;
		void initObjects() override;
		void initMoveAreas() override;

	private:
		// Level objects
		RoomSwitch room_switch;

		// Text
		sf::Font font;

		sf::Text text_1;
		sf::Text text_2;
};

#endif // ROOMENTRANCE_H