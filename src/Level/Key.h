
#ifndef KEY_H
#define KEY_H

#include "BaseClasses/GameObject.h"

#include <SFML/Graphics.hpp>

class Key: public GameObject
{
	// ----------------
	// 
	// A key object that can be used to open a door in the level somewhere
	// 
	// ----------------

public:
	Key();

	void update(float dt) override;
};

#endif // KEY_H