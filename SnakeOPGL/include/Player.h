#pragma once

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Game.h"
#include "Tile.h"
#include "glm/glm.hpp"
#include "Texture.h"
const int MAXSIZE = 100;
const int STARTSIZE = 3;

enum Direction
{
	DROITE,
	GAUCHE,
	HAUT,
	BAS
};
class Player {
	public:
		glm::ivec2 headPos;
		Direction curDir;
		Direction nextDir;
		std::vector<std::vector<Tile>>& map;
		Texture& headTexture;
		std::vector<GameObject> body;
		Player(Texture& headTexture, glm::ivec2 pos, std::vector<std::vector<Tile>>& map);
		void Move();
		void updatePos();
		void Draw(SpriteRenderer& renderer);
};