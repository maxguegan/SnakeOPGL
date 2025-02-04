#pragma once

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Tile.h"
#include "Game.h"
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
		glm::vec2 size;
		Direction curDir;
		Direction nextDir;
		std::vector<std::vector<Tile>>& map;
		Texture& headTexture;
		Texture& bodyTexture;
		Texture& tailTexture;
		std::vector<GameObject> body;
		glm::ivec2 position[MAXSIZE];
		Player(Texture& headTexture, Texture& bodyTexture, Texture& tailTexture, glm::ivec2 pos, glm::vec2 size, std::vector<std::vector<Tile>>& map);
		int Move();
		
		void Draw(SpriteRenderer& renderer);
private:
	void updatePos();
	void addSize();
};