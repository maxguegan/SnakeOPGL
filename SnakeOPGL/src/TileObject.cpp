#include "TileObject.h"

TileObject::TileObject(std::vector<std::vector<Tile>>& map, int x, int y, Texture tex, glm::vec2 size, glm::vec4 color, float rotation):map(map), tilePosX(x), tilePosY(y), GameObject(tex, map[y][x].position, size, color, rotation)
{}

void TileObject::setPos(const int x, const int y) {
	

	tilePosX = x;
	tilePosY = y;
	this->position = map[tilePosY][tilePosX].position;
}