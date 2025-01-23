#ifndef GWCRANK_H
#define GWCRANK_H

#include <BaseClasses/GameObject.h>
#include <BaseClasses/GimmickWindow.h>

#include <SFML/Graphics.hpp>

#include <iostream>

class GWCrank : public GimmickWindow
{
	// ----------------
	// 
	// When this window gets opened, the player gets prompted to crank a lever to progress further
	// 
	// ----------------

	public:
		// Public toggles
		float sprite_scale = 2.5;
		float crank_speed = 90;

		// Functions
		GWCrank();

		bool initGraphics() override;
		void initMovingObj(GameObject* obj, float max_y_pos);

		void onOpen() override;
		void onClose() override;
		void onComplete() override;

		void update(float dt) override;

		// Misc. variables
		std::shared_ptr<GameObject> moving_object;
		Vector2 moving_obj_start_pos;
		float moving_obj_max_y;

	private:
		float pi = 3.141592;

		bool is_holding_crank = false;
		float crank_total_rotation = 0;
		float prev_total_rot = 0;

		float crank_full_rotations = 0;

		// Graphics
		sf::Texture base_texture;
		sf::Texture lever_texture;
		sf::Texture background_texture;

		sf::Sprite base;
		sf::Sprite lever;
		sf::Sprite background;
};

#endif // GWCRANK_H