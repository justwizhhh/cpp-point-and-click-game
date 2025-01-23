
#include "RoomFinal.h"

#include <iostream>

RoomFinal::RoomFinal()
{
	name = "Final";

	initGraphics(
		"Data/Graphics/Levels/finalRoom_fg.png",
		"Data/Graphics/Levels/finalRoom_bg.png");
	initObjects();
	initMoveAreas();
}

void RoomFinal::initObjects()
{
	room_switch.position = Vector2(882, 496);
	room_switch.new_room_name = "Puzzle 3";
	room_switch.player_pos = Vector2(770, 474);
	room_switch.is_locked = false;
	room_switch.resetTexture();
	addToObjList(&room_switch);

	coffin.position = Vector2(504, 394);
	addToObjList(&coffin);
}

void RoomFinal::initMoveAreas()
{
	sf::IntRect area_1 = sf::IntRect(144, 188, 810, 240);
	sf::IntRect area_2 = sf::IntRect(144, 420, 188, 144);
	sf::IntRect area_3 = sf::IntRect(764, 420, 188, 144);
	sf::IntRect area_4 = sf::IntRect(336, 432, 76, 76);
	sf::IntRect area_5 = sf::IntRect(686, 432, 76, 76);

	move_areas.push_back(std::make_unique<sf::IntRect>(area_1));
	move_areas.push_back(std::make_unique<sf::IntRect>(area_2));
	move_areas.push_back(std::make_unique<sf::IntRect>(area_3));
	move_areas.push_back(std::make_unique<sf::IntRect>(area_4));
	move_areas.push_back(std::make_unique<sf::IntRect>(area_5));
}
