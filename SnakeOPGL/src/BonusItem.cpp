#include "BonusItem.h"
BonusItem::BonusItem(std::vector<std::vector<Tile>>& map, int x, int y, Texture tex, glm::vec2 pos, glm::vec2 size, int val, glm::vec4 col, float rotate):TileObject(map, x, y, tex, size,col,rotate) {
	value = val;
	}