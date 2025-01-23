
#include "Key.h"

#include <iostream>

Key::Key()
{
	initSprite("Data/Graphics/Objects/key.png");
	sprite.setOrigin(
		sf::Vector2f(
			sprite.getLocalBounds().width / 2, 
			sprite.getLocalBounds().width / 2));

	can_be_held = true;
}

void Key::update(float dt)
{
	GameObject::update(dt);
}