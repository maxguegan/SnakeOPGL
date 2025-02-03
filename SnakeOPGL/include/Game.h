#pragma once
#include <iostream>
#include <vector>
#include "Ressource.h"
#include "SpriteRenderer.h"
#include "Player.h"
#include "Tile.h"

enum GAMESTATE
{
	ACTIVE,
	PAUSE,
	OVER
};
const float maxTimer = 10.0f;
class Game {
public:
	bool keys[1024];
	static GAMESTATE state;
	const float width, height;
	std::vector<std::vector<Tile>> tiles;
	Game(const float width, const float height);
	void Init();
	void Render();
	void Update(float deltaTime);
	void ProcessInput();

private:
	const float tileSize = 21.0f;
	void InitMap();
	float timer = maxTimer;
};