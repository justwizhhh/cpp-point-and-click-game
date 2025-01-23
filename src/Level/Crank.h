#ifndef CRANK_H
#define CRANK_H

#include "BaseClasses/GameObject.h"
#include "Gimmicks/GWCrank.h"

#include <SFML/Graphics.hpp>

class Crank : public GameObject
{
	// ----------------
	// 
	// This object opens and closes the window for the crank gimmick segment of the game
	// 
	// ----------------

	public:
		Crank();

		void Open();
		void Close();

		GWCrank crank_window;

};

#endif // CRANK_H