
#ifndef COFFIN_H
#define COFFIN_H

#include "BaseClasses/GameObject.h"

#include <SFML/Graphics.hpp>

class Coffin : public GameObject
{
	// ----------------
	// 
	// The coffin acts as the goal object for the end of the game
	// 
	// ----------------

public:
	Coffin();
};

#endif // COFFIN_H