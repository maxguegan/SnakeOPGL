#pragma once
#include <iostream>
#include <vector>
#include "Ressource.h"
#include "SpriteRenderer.h"
#include "Player.h"
#include "Tile.h"
#include "BonusItem.h"
#include "TextRenderer.h"
#include "TileObject.h"
#include "UIText.h"
#include "Button.h"
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
	bool lockKeys[1024];
	GAMESTATE state;
	const float width, height;
	std::vector<std::vector<Tile>> tiles;
	int score;
	Game(const float width, const float height);
	void Init();
	void Render();
	void Update(float deltaTime);
	void ProcessInput();
	void ProcessMouse(double cursorPosX, double cursorPosY, GLFWwindow * window);
	void Restart();
private:
	const float tileSize = 30.0f;
	void InitMap();
	float timer = maxTimer;
};