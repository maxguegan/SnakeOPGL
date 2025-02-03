#pragma once
#include <glm/glm.hpp>

enum State
{
	EMPTY,
	SNAKE,
	BONUS
};
struct Tile
{
	glm::vec2 position;
	State state;
	Tile(glm::vec2 position);
};