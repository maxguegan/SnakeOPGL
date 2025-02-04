#include "BonusItem.h"
BonusItem::BonusItem(Texture tex, glm::vec2 pos, glm::vec2 size, int val, glm::vec4 col, float rotate):GameObject(tex, pos, size) {
	value = val;
	}