
#include "RoomPuzzle1.h"

#include <iostream>

RoomPuzzle1::RoomPuzzle1()
{
	name = "Puzzle 1";

	initGraphics(
		"Data/Graphics/Levels/room2_fg.png",
		"Data/Graphics/Levels/room2_bg.png");
	initText();
	initObjects();
	initMoveAreas();
}

void RoomPuzzle1::initText()
{
	if (!font.loadFromFile("Data/Fonts/Valley.ttf"))
	{
		std::cout << " Font for level text from not found!" << std::endl;
	}
	else
	{
		text_1.setString("Left-click on objects to"
			"\n\ninteract with them or pick them up");
		initTextObj(&text_1, &font, Vector2(100, 60), 24);

		text_2.setString("Press right-click to drop the currently" 
			"\n\nheld object");
		initTextObj(&text_2, &font, Vector2(100, 600), 24);

		level_text.push_back(std::make_shared<sf::Text>(text_1));
		level_text.push_back(std::make_shared<sf::Text>(text_2));
	}
}

void RoomPuzzle1::initObjects()
{
	room_switch.position = Vector2(760, 450);
	room_switch.new_room_name = "Puzzle 2";
	room_switch.player_pos = Vector2(868, 302);
	room_switch.player_face_right = false;
	room_switch.is_locked = true;
	room_switch.resetTexture();
	addToObjList(&room_switch);

	empty_vase1.position = Vector2(428, 356);
	addToObjList(&empty_vase1);

	empty_vase2.position = Vector2(448, 498);
	addToObjList(&empty_vase2);

	empty_vase3.position = Vector2(548, 498);
	addToObjList(&empty_vase3);

	key_vase.position = Vector2(508, 356);
	key_vase.contained_object = std::make_shared<GameObject>(key);
	addToObjList(&key_vase);

	key.is_active = false;
	addToObjList(&key);
}

void RoomPuzzle1::initMoveAreas()
{
	sf::IntRect area_1 = sf::IntRect(160, 260, 720, 250);

	move_areas.push_back(std::make_unique<sf::IntRect>(area_1));
}