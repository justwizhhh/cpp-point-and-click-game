
#include "GameObject.h"

#include <iostream>

GameObject::GameObject()
{
    is_active = true;

    pointer = std::shared_ptr<GameObject>(this);

    sprite.setScale(sf::Vector2f(sprite_scale, sprite_scale));
}

GameObject::~GameObject()
{

}

/*
    Loads in a main texture for the object's sprite to use, and also gives the
    object a new scale
*/

bool GameObject::initSprite(std::string file_path)
{
    if (!texture.loadFromFile(file_path))
    {
        std::cout << "Texture from " << file_path << "not found!" << std::endl;
        return false;
    }
    else
    {
        sprite.setTexture(texture);
        return true;
    }

    sprite.setScale(sf::Vector2f(sprite_scale, sprite_scale));
}

/*
    Get the current position of the object's centre area
*/

Vector2 GameObject::getCentrePosition()
{
    return 
        Vector2(
            position.x + (sprite.getGlobalBounds().width / 2), 
            position.y + (sprite.getGlobalBounds().height / 2));
}

/*
    Check if this object's sprite intersects with another object's sprite
*/

bool GameObject::intersects(sf::Sprite* obj)
{
    return 
        (sprite.getGlobalBounds().intersects(obj->getGlobalBounds()));
}

/*
    Check if this object's sprite overlaps with a position in-game
*/

bool GameObject::contains(Vector2* pos)
{
    return
        (sprite.getGlobalBounds().contains(Vector2::convertToSFFloat(pos)));
}

/*
    Take our position value and assign it to the object's actual sprite
*/

void GameObject::update(float dt)
{
    // Play an animation if the player tries to drop the object out-of-bounds
    if (is_playing_anim)
	{
        sprite.setRotation(original_angle +
            (sin(error_anim_clock.getElapsedTime().asSeconds() *
                anim_wavelength) *
                anim_amplitude));
            
        
        if (error_anim_clock.getElapsedTime().asSeconds() >= 
            current_anim_time + error_anim_time)
		{
            sprite.setColor(sf::Color::White);
            
            sprite.setRotation(0);
            is_playing_anim = false;
		}
	}

    updatePos();
}

/*
    Apply the position to the player's physical sprite location in-game
*/
void GameObject::updatePos()
{
    sprite.setPosition(position.x, position.y);
}

void GameObject::onPickUp()
{
    is_being_held = true;
}

void GameObject::onDrop()
{
    is_being_held = false;
}

/*
    Start error animation from the start
    For when the player tries to drop the object out of bounds
*/
void GameObject::playErrorAnim()
{
    sprite.setColor(sf::Color::Red);
    
    current_anim_time = error_anim_clock.getElapsedTime().asSeconds();
    is_playing_anim = true;
}
