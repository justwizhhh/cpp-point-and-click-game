#ifndef VASE_H
#define VASE_H

#include "BaseClasses/GameObject.h"

#include <SFML/Graphics.hpp>

class Vase: public GameObject
{
	// ----------------
	// 
	// A vase object that the player picks up and drops to reveal a new item
	// 
	// ----------------

	public:
		// Public toggles
		int max_click_count = 3;
		std::shared_ptr<GameObject> contained_object = nullptr;

		float click_anim_length = 0.16;
		float anim_wavelength = 60;
		float anim_amplitude = 3;
		
		// Functions
		Vase();
		void update(float dt) override;
		void onClick();

		bool is_destroyed = false;

	private:
		int click_count = 0;

		sf::Texture cracked_texture;

		// Animation features
		bool is_playing_anim = false;
		sf::Clock click_anim_timer;
		float current_time = 0;
		float original_x = 0;
};

#endif VASE_H
