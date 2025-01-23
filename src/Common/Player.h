
#ifndef PLATFORMER_PLAYER_H
#define PLATFORMER_PLAYER_H

#include "BaseClasses/GameObject.h"

class Player : public GameObject
{
	// ----------------
	// 
	// The player object that the user will move with the mouse
	// 
	// ----------------

	public:
		// Public toggles
		float move_speed = 5;
		float hover_amplitude = 1.5;
		float hover_speed = 11;
		float item_pos_offset = 22;
		
		// Functions
		Player();

		void flip(bool right);

		void setMoveTarget(Vector2 new_target);
		void cancelMove();

		void setHeldItem(std::shared_ptr<GameObject> new_item);
		void dropHeldItem();

		void update(float dt) override;

		// Misc. variables
		std::shared_ptr<GameObject> held_item = nullptr;

	private:
		Vector2 prev_position = Vector2(0, 0);

		void moveToTarget();
		bool is_moving = false;
		Vector2 move_target = Vector2(0, 0);

		float hover_progress = false;

		void updateHeldItem();
		bool is_holding_item = false;
};

#endif // PLATFORMER_PLAYER_H
