
#include "RoomPuzzle2.h"

#include <iostream>

RoomPuzzle2::RoomPuzzle2()
{
	name = "Puzzle 2";

	initGraphics(
		"Data/Graphics/Levels/room3_fg.png",
		"Data/Graphics/Levels/room3_bg.png");
	initObjects();
	initMoveAreas();
}

void RoomPuzzle2::initObjects()
{
	room_switch.position = Vector2(130, 352);
	room_switch.new_room_name = "Final";
	room_switch.player_pos = Vector2(210, 450);
	room_switch.is_locked = true;
	room_switch.resetTexture();
	addToObjList(&room_switch);

	addToObjList(&key);

	key_container.position = Vector2(530, -10);
	key_container.contained_key = std::make_shared<Key>(key);
	addToObjList(&key_container);

	crank.position = Vector2(244, 224);
	crank.crank_window.initMovingObj(&key_container, 330);
	addToObjList(&crank);

	gimmick_window = std::shared_ptr<GimmickWindow>(&crank.crank_window);
}

void RoomPuzzle2::initMoveAreas()
{
	sf::IntRect area_1 = sf::IntRect(112, 156, 828, 258);

	move_areas.push_back(std::make_unique<sf::IntRect>(area_1));
}