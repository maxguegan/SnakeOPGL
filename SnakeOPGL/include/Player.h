#pragma once

#include <iostream>
#include <vector>
#include "TileObject.h"
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
		glm::vec2 size;
		Direction curDir;
		Direction nextDir;
		std::vector<std::vector<Tile>>& map;
		std::vector<Effect> effects;
		std::vector<TileObject> body;
		Texture& headTexture;
		Texture& bodyTexture;	
		Texture& tailTexture;
		glm::vec4 color = glm::vec4(1.0f);
		float speed;
		
		Player(std::vector<std::vector<Tile>>& map, int startTilePosX, int startTilePosY, Texture& headTexture, Texture& bodyTexture, Texture& tailTexture, glm::vec2 size);
		int Move();
		void Draw(SpriteRenderer& renderer);
		void GameOver(int RestartTilePosX, int RestartTilePosY);
		void update(float deltaTime);
		void addBuff(Effect buff);
		void setColor(glm::vec4 color);
private:
	void Spawn(int StartTilePosX, int StartTilePosY);
	void updatePos(int headTilePosX, int headTilePosY);
	void addSize();
};