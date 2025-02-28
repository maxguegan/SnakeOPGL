#pragma once
#include "GameObject.h"
#include "Tile.h"
#include <vector>
class TileObject : public GameObject
{
public:
	int tilePosX;
	int tilePosY;
	std::vector<std::vector<Tile>>& map;
	TileObject(std::vector<std::vector<Tile>> & map,int x, int y,Texture tex, glm::vec2 size, glm::vec4 color = glm::vec4(1.0f), float rotation = 0.0f);
	void setPos(const int x, const int y);
};