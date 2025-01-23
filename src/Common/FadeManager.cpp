
#include "FadeManager.h"

#include <iostream>

void FadeManager::init(sf::Window* window)
{
	fade_rectangle.setPosition(0, 0);
	fade_rectangle.setFillColor(sf::Color::Black);
	fade_rectangle.setSize(sf::Vector2f(
		window->getSize().x, 
		window->getSize().y));
}

void FadeManager::playFadeIn(bool slow_mode)
{
	is_fading = true;
	is_slow = slow_mode;
	fade_progress = 0;

	is_fading_in = true;
	fade_rectangle.setFillColor(sf::Color(0, 0, 0, 255));
}

void FadeManager::playFadeOut(bool slow_mode)
{
	is_fading = true;
	is_slow = slow_mode;
	fade_progress = 0;

	is_fading_in = false;
	fade_rectangle.setFillColor(sf::Color(0, 0, 0, 0));
}

/*
	Updates the current state of the fading in/out animation
*/
void FadeManager::updateAnim(float dt)
{
	if (is_fading)
	{
		fade_progress += dt * (is_slow ? fade_speed_slow : fade_speed);

		// Stop the animation from playing just before it finishes
		if (fade_progress + (dt * fade_speed) >= 1)
		{
			is_fading = false;
			fade_progress = 1;
		}

		if (is_fading_in)
		{
			fade_rectangle.setFillColor(
				sf::Color(0, 0, 0, 255 - (255 * fade_progress)));
		}
		else
		{
			fade_rectangle.setFillColor(
				sf::Color(0, 0, 0, 255 * fade_progress));
		}
	}
}
