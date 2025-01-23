
#ifndef ROOMSWITCH_H
#define ROOMSWITCH_H

#include "BaseClasses/GameObject.h"
#include "BaseClasses/Vector2.h"

#include <SFML/Graphics.hpp>

class RoomSwitch : public GameObject
{
	// ----------------
	// 
	// If the player touches this object, they get sent to another room
	// 
	// ----------------

public:
	RoomSwitch();

	// Public toggles
	std::string new_room_name = "";
	Vector2 player_pos = Vector2(0, 0);
	bool player_face_right = true;
	bool is_locked = false;

	// Functions
	bool resetTexture();
	void unlockDoor();

private:
	sf::Texture locked_texture;
};

#endif // ROOMSWITCH_H