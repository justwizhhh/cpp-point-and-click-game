
#include "RoomPuzzle3.h"

#include <iostream>

RoomPuzzle3::RoomPuzzle3()
{
	name = "Puzzle 3";

	initGraphics(
		"Data/Graphics/Levels/room4_fg.png",
		"Data/Graphics/Levels/room4_bg.png");
	initObjects();
	initMoveAreas();
}

void RoomPuzzle3::initObjects()
{
	room_switch.position = Vector2(690, 496);
	room_switch.new_room_name = "Final";
	room_switch.player_pos = Vector2(780, 450);
	room_switch.player_face_right = false;
	room_switch.is_locked = false;
	room_switch.resetTexture();
	addToObjList(&room_switch);

	key.position = Vector2(888, 432);
	addToObjList(&key);
}

void RoomPuzzle3::initMoveAreas()
{
	sf::IntRect area_1 = sf::IntRect(686, 394, 256, 166);

	move_areas.push_back(std::make_unique<sf::IntRect>(area_1));
}
