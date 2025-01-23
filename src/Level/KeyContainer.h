#ifndef KEYCONTAINER_H
#define KEYCONTAINER_H

#include "BaseClasses/Vector2.h"
#include "BaseClasses/GameObject.h"
#include "Key.h"

class KeyContainer : public GameObject
{
	public:
		KeyContainer();

		void update(float dt) override;
		
		std::shared_ptr<Key> contained_key = nullptr;
		Vector2 offset;
};

#endif // KEYCONTAINER_H