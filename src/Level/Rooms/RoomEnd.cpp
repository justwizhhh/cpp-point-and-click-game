
#include "RoomEnd.h"

#include <iostream>

RoomEnd::RoomEnd()
{
	name = "End";
	hide_player = true;

	initGraphics(
		"Data/Graphics/Levels/endRoom_fg.png",
		"Data/Graphics/Levels/endRoom_bg.png");
	initText();
}

void RoomEnd::initText()
{
	if (!font.loadFromFile("Data/Fonts/Valley.ttf"))
	{
		std::cout << " Font for level text from not found!" << std::endl;
	}
	else
	{
		text_1.setString("The zombie has been reanimated...");
		initTextObj(&text_1, &font, Vector2(150, 70), 24);

		text_2.setString("Thank you for playing!");
		initTextObj(&text_2, &font, Vector2(214, 620), 30);

		level_text.push_back(std::make_shared<sf::Text>(text_1));
		level_text.push_back(std::make_shared<sf::Text>(text_2));
	}
}