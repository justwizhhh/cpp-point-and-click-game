
#include "Vase.h"

#include <iostream>

Vase::Vase()
{
	initSprite("Data/Graphics/Objects/vase.png");
	sprite.setOrigin(
		sf::Vector2f(
			sprite.getLocalBounds().width / 2,
			sprite.getLocalBounds().width / 2));

	if (!cracked_texture.loadFromFile("Data/Graphics/Objects/vaseCracked.png"))
	{
		std::cout << "Texture for cracked vase not found!" << std::endl;
	}
}

void Vase::onClick()
{
	click_count++;

	sprite.setTexture(cracked_texture);

	// Plays a quick shaking animation
	original_x = sprite.getPosition().x;
	current_time = click_anim_timer.getElapsedTime().asSeconds();
	is_playing_anim = true;

	if (click_count >= max_click_count)
	{
		is_destroyed = true;

		is_active = false;

		if (contained_object != nullptr)
		{
			contained_object->pointer->is_active = true;
			contained_object->pointer->position = position;
		}
	}
}

void Vase::update(float dt)
{
	if (is_playing_anim)
	{
		position.x = 
			original_x + 
			(sin(click_anim_timer.getElapsedTime().asSeconds() * 
				anim_wavelength) * 
			anim_amplitude);

		if (click_anim_timer.getElapsedTime().asSeconds() >= 
			current_time + click_anim_length)
		{
			is_playing_anim = false;
			position.x = original_x;
		}
	}

	updatePos();
}

