#pragma once
#include "GameObject.h"

class BonusItem : public GameObject
{

public:
	int value;
	BonusItem(Texture tex, glm::vec2 pos, glm::vec2 size, int val = 100, glm::vec4 col = glm::vec4(1.0f), float rotate = 0.0f);
	

	
};
