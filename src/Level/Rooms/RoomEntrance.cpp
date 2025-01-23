
#include "RoomEntrance.h"

#include <iostream>

RoomEntrance::RoomEntrance()
{
	name = "Entrance";

	initGraphics(
		"Data/Graphics/Levels/room1_fg.png",
		"Data/Graphics/Levels/room1_bg.png");
	initText();
	initObjects();
	initMoveAreas();
}

void RoomEntrance::initText()
{
	if (!font.loadFromFile("Data/Fonts/Valley.ttf"))
	{
		std::cout << " Font for level text from not found!" << std::endl;
	}
	else
	{
		text_1.setString("Resurrection \n \n a point and click game");
		initTextObj(&text_1, &font, Vector2(180, 160), 24);

		text_2.setString("Press left-click to move to" 
			"\n \n the position of your cursor");
		initTextObj(&text_2, &font, Vector2(420, 380), 14);

		level_text.push_back(std::make_shared<sf::Text>(text_1));
		level_text.push_back(std::make_shared<sf::Text>(text_2));
	}
}

void RoomEntrance::initObjects()
{
	room_switch.position = Vector2(870, 500);
	room_switch.new_room_name = "Puzzle 1";
	room_switch.player_pos = Vector2(210, 450);
	room_switch.is_locked = false;
	addToObjList(&room_switch);
}

void RoomEntrance::initMoveAreas()
{
	sf::IntRect area_1 = sf::IntRect(170, 160, 610, 190);
	sf::IntRect area_2 = sf::IntRect(260, 300, 680, 200);
	sf::IntRect area_3 = sf::IntRect(590, 450, 350, 100);
	
	move_areas.push_back(std::make_unique<sf::IntRect>(area_1));
	move_areas.push_back(std::make_unique<sf::IntRect>(area_2));
	move_areas.push_back(std::make_unique<sf::IntRect>(area_3));
}
