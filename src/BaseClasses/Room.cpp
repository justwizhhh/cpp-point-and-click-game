
#include "Room.h"

#include <iostream>

Room::Room()
{
    bg_sprite.setScale(sf::Vector2f(sprite_scale, sprite_scale));
    fg_sprite.setScale(sf::Vector2f(sprite_scale, sprite_scale));
}
/*
    Load in all foreground and background graphics for the level
*/
bool Room::initGraphics(std::string fg_file_path, std::string bg_file_path)
{
    if (!fg_texture.loadFromFile(fg_file_path))
    {
        std::cout << " Foreground scenery texture from " 
            << fg_file_path 
            << "not found!" << std::endl;
        return false;
    }
    else
    {
        fg_sprite.setTexture(fg_texture);
    }

    if (!bg_texture.loadFromFile(bg_file_path))
    {
        std::cout << " Background scenery texture from " 
            << bg_file_path 
            << "not found!" << std::endl;
        return false;
    }
    else
    {
        bg_sprite.setTexture(bg_texture);
    }

    return true;
}

/*
    This takes the current text object, and give it a set size (scale), 
    position, and optionally a new colour as well
 */
void Room::initTextObj(sf::Text* text, sf::Font* font, const Vector2& position, 
    int scale, sf::Color color)
{
    text->setFont(*font);
    text->setCharacterSize(scale);
    text->setPosition(position.x, position.y);
    text->setFillColor(color);
    font->setSmooth(false);
}

/*
    This will allow Game.cpp to access and update all of the objects in the 
    currently-loaded room
*/

void Room::addToObjList(GameObject* obj)
{
    obj->updatePos();
    level_objects.push_back(std::make_shared<GameObject>(*obj));
}
