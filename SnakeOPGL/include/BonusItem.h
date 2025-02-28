#pragma once
#include "TileObject.h"
#include "Effect.h"
#include "Ressource.h"
class BonusItem : public TileObject
{

public:
	EFFECTTYPE effect;
	int value;
	
	BonusItem(std::vector<std::vector<Tile>>& map , int x, int y, Texture tex, glm::vec2 pos, glm::vec2 size, int val = 100, glm::vec4 col = glm::vec4(1.0f), float rotate = 0.0f);
	void MoveBonus();
	void draw(SpriteRenderer& renderer);
	
};
