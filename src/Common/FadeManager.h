#ifndef FADEMANAGER_H
#define FADEMANAGER_H

#include <SFML/Graphics.hpp>

class FadeManager
{
	// ----------------
	// 
	// This object controls global fading animations throughout the game
	// 
	// ----------------

	public:
		// Public toggles
		float fade_speed = 1.5;
		float fade_speed_slow = 0.3;

		// Functions
		void init(sf::Window* window);
		void playFadeIn(bool slow_mode);
		void playFadeOut(bool slow_mode);
		void updateAnim(float dt);

		// Misc.
		sf::RectangleShape fade_rectangle;

	private:
		bool is_fading = false;
		bool is_fading_in = false;
		bool is_slow = false;
		float fade_progress = 0;
};

#endif FADEMANAGER_H