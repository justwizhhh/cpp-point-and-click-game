
#include "GWCrank.h"

#include <iostream>

GWCrank::GWCrank()
{
	initGraphics();
	is_opened = false;
}

bool GWCrank::initGraphics()
{
	if (!background_texture.loadFromFile(
		"Data/Graphics/Objects/crankWindowBG.png"))
	{
		std::cout << "Crank background texture could not be loaded in";
		return false;
	}

	background.setTexture(background_texture);
	background.setOrigin(
		background_texture.getSize().x / 2, 
		background_texture.getSize().y / 2);
	background.setScale(sprite_scale, sprite_scale);
	background.setPosition(528, 346);
	background.setColor(sf::Color(255, 255, 255, 130));
	
	if (!base_texture.loadFromFile(
		"Data/Graphics/Objects/crankBase.png"))
	{
		std::cout << "Crank base texture could not be loaded in";
		return false;
	}

	base.setTexture(base_texture);
	base.setOrigin(
		base_texture.getSize().x / 2, 
		base_texture.getSize().y / 2);
	base.setScale(sprite_scale, sprite_scale);
	base.setPosition(528, 346);

	if (!lever_texture.loadFromFile(
		"Data/Graphics/Objects/crankLever.png"))
	{
		std::cout << "Crank lever texture could not be loaded in";
		return false;
	}

	lever.setTexture(lever_texture);
	lever.setOrigin(
		lever_texture.getSize().x / 2, 
		lever_texture.getSize().y - 5);
	lever.setScale(sprite_scale, sprite_scale);
	lever.setPosition(528, 346);

	sprites.push_back(std::shared_ptr<sf::Sprite>(&background));
	sprites.push_back(std::shared_ptr<sf::Sprite>(&base));
	sprites.push_back(std::shared_ptr<sf::Sprite>(&lever));

	return true;
}

void GWCrank::initMovingObj(GameObject* obj, float max_y_pos)
{
	moving_object = std::shared_ptr<GameObject>(obj);
	moving_obj_start_pos = moving_object->position;
	moving_obj_max_y = max_y_pos;
}

void GWCrank::onOpen()
{
	is_opened = true;
}

void GWCrank::onClose()
{
	is_opened = false;
}

void GWCrank::onComplete()
{
	is_opened = false;
	is_completed = true;

	is_holding_crank = false;
	is_mouse_held = false;
}

void GWCrank::update(float dt)
{
	if (is_opened && !is_completed)
	{
		if (is_mouse_held)
		{
			if (lever.getGlobalBounds().contains(
				mouse_pos.x, mouse_pos.y))
			{
				is_holding_crank = true;

				// Update the lever's new rotation
				float new_angle = (atan2(
					mouse_pos.y - lever.getPosition().y,
					mouse_pos.x - lever.getPosition().x) * 180 / pi) + 90;

				if (new_angle <= 0) { new_angle += 360; }

				// Track how many times the lever has been fully rotated
				float angle_diff = (new_angle - lever.getRotation());
				if (abs(angle_diff) < 90)
				{
					crank_total_rotation += angle_diff;
				}
				else
				{
					crank_total_rotation += 
						angle_diff + (360 * ((signbit(angle_diff) * 2) - 1));
				}

				// Check if the mouse is still holding onto the crank
				if (!lever.getGlobalBounds().
					contains(mouse_pos.x, mouse_pos.y))
				{
					is_holding_crank = false;
					mouseRelease();
				}
				else
				{
					crank_full_rotations = crank_total_rotation / 360;
					lever.setRotation(new_angle);
				}

				prev_total_rot = angle_diff;
			}
		}

		// Changing the position of whatever object the crank is influencing
		if (moving_object != nullptr)
		{
			if (is_holding_crank)
			{
				// Whether the crank moves clockwise or counter-clockwise
				float abs_rotation = abs(crank_full_rotations);

				if (abs_rotation >= 0)
				{
					moving_object->pointer->position =
						Vector2(
							moving_obj_start_pos.x,
							moving_obj_start_pos.y +
							(abs_rotation * crank_speed));
				}

				if (moving_object->pointer->position.y >= moving_obj_max_y)
				{
					onComplete();
				}
			}
		}
	}
};