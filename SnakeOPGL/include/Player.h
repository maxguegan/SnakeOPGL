#pragma once

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Tile.h"
#include "Game.h"
#include "glm/glm.hpp"
#include "Texture.h"
#include "Effect.h"
const int MAXSIZE = 100;
const int STARTSIZE = 3;
const int BASESPEED = 20.0f;
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
		std::vector<Effect> effects;
		Texture& headTexture;
		Texture& bodyTexture;
		Texture& tailTexture;

		float speed;

		std::vector<GameObject> body;
		glm::ivec2 position[MAXSIZE];
		Player(Texture& headTexture, Texture& bodyTexture, Texture& tailTexture, glm::ivec2 pos, glm::vec2 size, std::vector<std::vector<Tile>>& map);
		int Move();
		void Draw(SpriteRenderer& renderer);
		void GameOver(glm::ivec2 resPos);
		void update(float deltaTime);
private:
	void Spawn(glm::ivec2 resPos);
	void updatePos();
	void addSize();
};