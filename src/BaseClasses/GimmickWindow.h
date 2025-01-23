#ifndef GIMMICKWINDOW_H
#define GIMMICKWINDOW_H

#include "BaseClasses/Vector2.h"

#include <iostream>

class GimmickWindow
{
	// ----------------
	// 
	// This base class will allow pop-up windows to be used in levels for puzzle-solving sequences
	// This will also prevent all other level interactions occuring while the pop-up window is open
	// 
	// ----------------

	public:
		// Functions
		virtual bool initGraphics();

		virtual void onOpen();
		virtual void onClose();
		virtual void onComplete();

		void mouseClick(Vector2 new_pos);
		void mouseRelease();
		virtual void update(float dt) { };

		// Misc. variables
		bool is_opened = true;
		bool is_completed = false;

		bool is_mouse_held = false;
		Vector2 mouse_pos;

		std::vector<std::shared_ptr<sf::Sprite>> sprites;
};

#endif // GIMMICKWINDOW_H