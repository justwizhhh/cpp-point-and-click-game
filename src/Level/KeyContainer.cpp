
#include "KeyContainer.h"

KeyContainer::KeyContainer()
{
	initSprite("Data/Graphics/Objects/chainedCell.png");
	sprite.setOrigin(sf::Vector2f(
		sprite.getLocalBounds().width / 2,
		sprite.getLocalBounds().height));

	offset = Vector2(0, -48);

	is_active = true;
}

void KeyContainer::update(float dt)
{
	if (contained_key != nullptr)
	{
		contained_key->pointer->position = position + offset;
		if (contained_key->pointer->is_being_held)
		{
			// No longer keep the key trapped once the player has picked it up
			contained_key = nullptr;
		}
	}

	updatePos();
}
