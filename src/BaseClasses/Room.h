
#ifndef ROOM_H
#define ROOM_H

#include "BaseClasses/Vector2.h"
#include "BaseClasses/GameObject.h"
#include "BaseClasses/GimmickWindow.h"

#include <SFML/Graphics.hpp>

#include <iostream>

class Room
{
	// ----------------
	// 
	// The base class for all of the game's levels (and all objects that are 
	// loaded inside of them)
	// 
	// ----------------

	public:
		// Public toggles
		float sprite_scale = 3;
		std::string name;
		bool hide_player = false;
	
		// Functions
		Room();

		bool initGraphics(std::string fg_file_path, std::string bg_file_path);
		virtual void initText() { }
		void initTextObj(
			sf::Text* text, 
			sf::Font* font,
			const Vector2& position, 
			int scale, 
			sf::Color color = sf::Color::White);

		virtual void initMoveAreas() { };
		virtual void initObjects() { };
		void addToObjList(GameObject* obj);

		// Main level assets
		std::vector<std::shared_ptr<sf::IntRect>> move_areas;
		std::vector<std::shared_ptr<GameObject>> level_objects;
		std::shared_ptr<GimmickWindow> gimmick_window = nullptr;

		// Misc. variables
		std::vector<std::shared_ptr<sf::Text>> level_text;

		sf::Sprite fg_sprite;
		sf::Sprite bg_sprite;
		sf::Texture fg_texture;
		sf::Texture bg_texture;
};

#endif // ROOM_H