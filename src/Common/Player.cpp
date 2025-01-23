
#include "Player.h"

Player::Player()
{
	initSprite("Data/Graphics/Player/playerIdle.png");
	sprite.setOrigin(sf::Vector2f(0.5, 0.5));
}

/*
	Horiztonally flip the player's texture to face the other way
*/
void Player::flip(bool right)
{
	if (right)
	{
		sprite.setTextureRect(
			sf::IntRect(
				0, 0,
				texture.getSize().x, texture.getSize().y));
	}
	else
	{
		sprite.setTextureRect(
			sf::IntRect(
				texture.getSize().x, 0,
				-texture.getSize().x, texture.getSize().y));
	}
}

/*
	Give the player a new "target" position to start moving towards to
*/

void Player::setMoveTarget(Vector2 new_target)
{
	move_target = new_target;
	flip(move_target.x >= getCentrePosition().x);
	is_moving = true;
}

/*
	Move the player to the new position specified by the user's cursor
*/

void Player::moveToTarget()
{
	float distance = 
		Vector2(
			getCentrePosition().x - move_target.x, 
			getCentrePosition().y - move_target.y).getMagnitude();

	if (!move_target.checkIfNull() && floor(distance) > move_speed)
	{
		Vector2 dir = 
			Vector2(
				getCentrePosition().x - move_target.x, 
				getCentrePosition().y - move_target.y);
		dir = dir.getNormalised() * -1;

		velocity = Vector2(
			dir.x * move_speed, 
			(dir.y * move_speed) + (sin(hover_progress) * hover_amplitude));
	}
	else
	{
		// Stop moving if the player is mostly close enough
		position =
			move_target - 
			Vector2(
				sprite.getGlobalBounds().width / 2,
				sprite.getGlobalBounds().height / 2);
		cancelMove();
	}
}

void Player::cancelMove()
{
	position = prev_position;
	velocity = Vector2(0, 0);
	is_moving = false;
}

/*
	Give the player a new object to hold on to
*/

void Player::setHeldItem(std::shared_ptr<GameObject> new_item)
{
	is_holding_item = true;
	held_item = new_item;
}

void Player::updateHeldItem()
{
	held_item->position = Vector2(
		position.x + (held_item->sprite.getGlobalBounds().width),
		position.y + sprite.getGlobalBounds().height + item_pos_offset);
}

/*
	Dispose of the currently-held object. The player will be able to pick up
	this object later if they want
*/

void Player::dropHeldItem()
{
	if (held_item != nullptr)
	{
		is_holding_item = false;
		held_item->onDrop();
		held_item = nullptr;
	}
}

void Player::update(float dt)
{
	if (is_moving)
	{
		moveToTarget();
	}

	if (held_item != nullptr)
	{
		updateHeldItem();
	}

	hover_progress += hover_speed * dt;
	
	prev_position = position;
	position += velocity;
	updatePos();
}