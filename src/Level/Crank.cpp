
#include "Crank.h"

Crank::Crank()
{
	initSprite("Data/Graphics/Objects/crank.png");
	sprite.setOrigin(sf::Vector2f(0.5, 0.5));
}

void Crank::Open()
{
	if (!crank_window.is_opened && !crank_window.is_completed)
	{
		crank_window.onOpen();
	}
}

void Crank::Close()
{
	if (crank_window.is_opened)
	{
		crank_window.onClose();
	}
}
