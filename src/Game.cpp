
#include "Game.h"

#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
	srand(time(NULL));
}

bool Game::init()
{
	player.position = Vector2(220, 284);

	current_room = std::make_unique<Room>(room_1);

	initRooms();
	initGraphics();
	initUI();

	return true;
}

/*
	Load in all of the game's rooms
*/

bool Game::initRooms()
{
	rooms.insert(std::make_pair(
		room_1.name,
		std::make_unique<Room>(room_1)));
	rooms.insert(std::make_pair(
		room_2.name,
		std::make_unique<Room>(room_2)));
	rooms.insert(std::make_pair(
		room_3.name,
		std::make_unique<Room>(room_3)));
	rooms.insert(std::make_pair(
		room_4.name,
		std::make_unique<Room>(room_4)));
	rooms.insert(std::make_pair(
		room_final.name,
		std::make_unique<Room>(room_final)));
	rooms.insert(std::make_pair(
		room_end.name,
		std::make_unique<Room>(room_end)));

	if (rooms.empty())
	{
		std::cout << "No rooms have been loaded in!" << std::endl;
		return false;
	}
	
	return true;
}

/*
	Load in all of the game's graphics 
	(that aren't for game-objects specifically)
*/

bool Game::initGraphics()
{
	return true;
}

/*
	Load in all of the game's UI elements
*/

bool Game::initUI()
{
	fade_manager.init(&window);
	fade_manager.playFadeIn(true);
	return true;
}

void Game::mouseClicked(sf::Event event)
{
	is_mouse_held = true;
	
	// Interact button
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i click_pos = 
			static_cast<sf::Vector2i>(window.mapPixelToCoords(
				sf::Mouse::getPosition(window), window.getView()));

		Vector2 click_vector = Vector2(click_pos.x, click_pos.y);

		// Mouse-controlled player/mouse interactions
		for (auto& area : current_room->move_areas)
		{
			bool loop_done = false;

			// Don't process mouse input if a gimmick window is open
			if (current_window != nullptr)
			{
				if (current_window->is_opened)
				{
					loop_done = true;
				}
			}
			
			// Object interactions
			if (area->contains(click_pos))
			{
				for (auto& level_obj : current_room->level_objects)
				{
					std::shared_ptr<GameObject> obj = 
						level_obj->pointer;

					if (obj->is_active)
					{
						// Vases
						std::shared_ptr<Vase> vase = 
							std::dynamic_pointer_cast<Vase>(obj);

						if (vase)
						{
							if (vase->contains(&click_vector))
							{
								if (!vase->is_destroyed)
								{
									vase->onClick();
									loop_done = true;
									break;
								}
							}
						}
					}
				}

				if (loop_done)
				{
					break;	
				}
				else
				{
					// Only move the player if they aren't trying to click on 
					// an object
					player.setMoveTarget(click_vector);
				}
			}
		}
	}
	
	else if (event.mouseButton.button == sf::Mouse::Right)
	{
		// If not in a gimmick window, drop the currently-held item
		if (player.held_item != nullptr)
		{
			bool has_dropped = false;
			for (auto& area : current_room->move_areas)
			{
				if (area->contains(
					Vector2::convertToSFInt(&player.held_item->position)))
				{
					player.dropHeldItem();
					has_dropped = true;
					break;
				}
			}
			if (!has_dropped)
			{
				// Play error animation if item cannot be dropped
				player.held_item->playErrorAnim();
			}
		}
	}
}

void Game::mouseHeld()
{
	sf::Vector2i click_pos =
		static_cast<sf::Vector2i>(window.mapPixelToCoords(
			sf::Mouse::getPosition(window), window.getView()));

	Vector2 click_vector = Vector2(click_pos.x, click_pos.y);
	
	// Gimmick window interaction
	if (current_window != nullptr)
	{
		current_window->mouseClick(click_vector);
	}
}

void Game::mouseReleased(sf::Event event)
{
	is_mouse_held = false;
	
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		// Gimmick window interaction
		if (current_window != nullptr)
		{
			current_window->mouseRelease();
		}
	}
}

/*
	Load in a new room and set that to be the main room to update and render
*/

void Game::loadNewRoom(std::string new_room_name, bool slow_fade)
{
	if (rooms.find(new_room_name) != rooms.end())
	{
		std::shared_ptr<Room> new_room = rooms.find(new_room_name)->second;

		// Transfer currently-held items from the previous room to the next
		if (player.held_item != nullptr)
		{
			new_room->level_objects.push_back(player.held_item->pointer);
			
			std::vector<std::shared_ptr<GameObject>>::iterator obj_index = 
				std::find(
					current_room->level_objects.begin(),
					current_room->level_objects.end(),
					player.held_item->pointer);

			if (obj_index != current_room->level_objects.end())
			{
				current_room->level_objects.erase(obj_index);
			}
		}

		current_room = new_room;

		// Find a gimmick window to open if the current room has one
		if (current_room->gimmick_window != nullptr)
		{
			current_window = current_room->gimmick_window;
		}

		player.is_active = !current_room->hide_player;

		fade_manager.playFadeIn(slow_fade);
	}
}

void Game::update(float dt)
{
	// Mouse interactions
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		mouseHeld();
	}

	// General object interactions
	for (int i = 0; i < current_room->level_objects.size(); i++)
	{
		// Use the smart pointer directly without extracting raw pointers
		std::shared_ptr<GameObject> obj =
			current_room->level_objects.at(i)->pointer;

		if (obj->is_active)
		{
			// Check to see if any of the on-screen level objects can be 
			// picked up by the player
			if (!player.held_item)
			{
				// Keys
				std::shared_ptr<Key> key =
					std::dynamic_pointer_cast<Key>(obj);

				if (key != nullptr)
				{
					if (key->can_be_held)
					{
						if (player.intersects(&(key->sprite))
							&& !key->is_being_held)
						{
							key->is_being_held = true;
							key->onPickUp();
							player.setHeldItem(key);
						}
					}
				}
			}

			// Doors
			std::shared_ptr<RoomSwitch> room_switch =
				std::dynamic_pointer_cast<RoomSwitch>(obj);

			if (room_switch != nullptr)
			{
				if (player.intersects(&(room_switch->sprite)))
				{
					// Locked doors require the player to hold a key
					if (room_switch->is_locked)
					{
						if (!player.velocity.checkIfNull())
						{
							if (player.held_item != nullptr &&
								std::dynamic_pointer_cast<Key>
								(player.held_item) != nullptr)
							{
								room_switch->unlockDoor();
								player.held_item->is_active = false;
								player.dropHeldItem();
							}
						}
					}
					else
					{
						if (player.velocity.checkIfNull())
						{
							loadNewRoom(room_switch->new_room_name, false);

							player.setMoveTarget(
								room_switch->player_pos
								- (player.position
									- player.getCentrePosition()));
							player.flip(room_switch->player_face_right);
							player.cancelMove();
							player.position = room_switch->player_pos;
						}
					}
				}
			}

			// Cranks
			std::shared_ptr<Crank> crank =
				std::dynamic_pointer_cast<Crank>(obj);

			if (crank != nullptr)
			{
				if (player.intersects(&(crank->sprite)))
				{
					if (!crank->crank_window.is_completed
						&& player.velocity.checkIfNull())
					{
						player.cancelMove();
						crank->Open();
					}
				}
			}

			// The end-game coffin
			std::shared_ptr<Coffin> coffin =
				std::dynamic_pointer_cast<Coffin>(obj);

			if (coffin != nullptr)
			{
				if (player.intersects(&(coffin->sprite)))
				{
					if (std::dynamic_pointer_cast<Key>
						(player.held_item) != nullptr)
					{
						player.cancelMove();
						player.held_item->is_active = false;
						player.dropHeldItem();
						loadNewRoom("End", true);
					}
				}
			}

			obj->update(dt);
		}
	}

	// Updating the currently-opened gimmick window
	if (current_window != nullptr)
	{
		if (current_window->is_opened)
		{
			current_window->update(dt);
		}
	}

	// Basic player collision detection
	// Stop the player from leaving a move area inside the current room
	int areas_covered = 0;
	for (auto& area : current_room->move_areas)
	{
		Vector2 col_pos_check = player.getCentrePosition() + player.velocity;
		if (area->contains(
			Vector2::convertToSFInt(&col_pos_check)))
		{
			areas_covered++;
		}
	}

	if (areas_covered <= 0)
	{
		player.cancelMove();
	}

	// Updating player positions
	player.update(dt);

	// UI updates
	fade_manager.updateAnim(dt);
}

void Game::render()
{
	window.draw(current_room->bg_sprite);

	// Level object rendering
	for (auto obj : current_room->level_objects)
	{
		if (obj->pointer->is_active)
		{
			window.draw(obj->pointer->sprite);

		}
	}
	window.draw(current_room->fg_sprite);

	// Level text rendering
	for (auto text : current_room->level_text)
	{
		window.draw(*text);
	}

	if (player.is_active)
	{
		window.draw(player.sprite);
	}

	// Level gimmick window rendering
	if (current_window != nullptr)
	{
		for (const auto& sprite : current_window->sprites)
		{
			if (current_window->is_opened)
			{
				window.draw(*sprite);
			}
		}
	}

	// UI
	window.draw(fade_manager.fade_rectangle);
}


