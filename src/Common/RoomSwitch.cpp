
#include "RoomSwitch.h"

#include <iostream>

RoomSwitch::RoomSwitch()
{
	initSprite("Data/Graphics/Objects/door.png");
	sprite.setOrigin(sf::Vector2f(0.5, 0.5));
	
	is_active = true;

	resetTexture();
}

bool RoomSwitch::resetTexture()
{
	if (is_locked)
	{
		if (!locked_texture.loadFromFile(
			"Data/Graphics/Objects/lockedDoor.png"))
		{
			std::cout << "Texture for locked door not found!" << std::endl;
			return false;
		}
		else
		{
			sprite.setTexture(locked_texture);
			return true;
		}
	}
	else
	{
		return false;
	}
}

void RoomSwitch::unlockDoor()
{
	is_locked = false;
	sprite.setTexture(texture);
}
