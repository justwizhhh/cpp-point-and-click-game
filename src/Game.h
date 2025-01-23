
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include "Common/Player.h"
#include "Common/FadeManager.h"
#include "BaseClasses/Room.h"
#include "BaseClasses/GimmickWindow.h"

#include "Level/Rooms/RoomEntrance.h"
#include "Level/Rooms/RoomPuzzle1.h"
#include "Level/Rooms/RoomPuzzle2.h"
#include "Level/Rooms/RoomPuzzle3.h"
#include "Level/Rooms/RoomFinal.h"
#include "Level/Rooms/RoomEnd.h"

#include "Level/Gimmicks/GWCrank.h"

#include <SFML/Graphics.hpp>

class Game
{
	// ----------------
	// 
	// This is where all central game data is stored and ran. All object
	// behaviours are set to be executed and rendered from this script
	// 
	// ----------------

	public:
		Game(sf::RenderWindow& window);

		// Functions
		bool init();
		bool initRooms();
		bool initGraphics();
		bool initUI();

		void mouseClicked(sf::Event event);
		void mouseHeld();
		void mouseReleased(sf::Event event);

		void loadNewRoom(std::string new_room_name, bool slow_fade);

		void update(float dt);
		void render();

	private:
		bool is_mouse_held = false;
		sf::RenderWindow& window;
  
		// Game rooms
		RoomEntrance room_1;
		RoomPuzzle1 room_2;
		RoomPuzzle2 room_3;
		RoomPuzzle3 room_4;
		RoomFinal room_final;
		RoomEnd room_end;

		std::map<std::string, std::shared_ptr<Room>> rooms;
		std::shared_ptr<Room> current_room = nullptr;

		// Game objects
		Player player;

		std::shared_ptr<GimmickWindow> current_window = nullptr;

		// UI objects
		FadeManager fade_manager;
};

#endif // PLATFORMER_GAME_H
