
#ifndef PLATFORMER_GAMEOBJECT_H
#define PLATFORMER_GAMEOBJECT_H

#include "Vector2.h"

#include <SFML/Graphics.hpp>

class GameObject
{
	// ----------------
	// 
	// The base class for all interactive game-objects in the game
	// 
	// ----------------

	public:
		GameObject();
		~GameObject();

		// Public toggles
		float sprite_scale = 3;
		float error_anim_time = 0.3;
		float anim_wavelength = 70;
		float anim_amplitude = 4;
		bool can_be_held = false;

		// General behaviour
		bool is_active = false;
		std::shared_ptr<GameObject> pointer = nullptr;

		sf::Texture texture;
		sf::Sprite sprite;
		bool initSprite(std::string file_path);

		Vector2 position = Vector2(0, 0);
		Vector2 velocity = Vector2(0, 0);
		Vector2 getCentrePosition();

		bool intersects(sf::Sprite* obj);
		bool contains(Vector2* pos);

		virtual void update(float dt);
		void updatePos();

		// Pick-up behaviour (if the object can even be picked up)
		bool is_being_held = false;

		virtual void onPickUp();
		virtual void onDrop();

		void playErrorAnim();

	private:
		// Animation info
		bool is_playing_anim = false;
		sf::Clock error_anim_clock;
		float current_anim_time = 0;
		float original_angle = 0;
};

#endif // PLATFORMER_GAMEOBJECT_H