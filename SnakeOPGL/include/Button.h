#pragma once
#include "GameObject.h"
#include "TextRenderer.h"
#include <glm/glm.hpp>
#include <string>
class Button {

public:
	TextRenderer& textRenderer;
	GameObject backGround;
	Button(glm::vec2 pos, glm::vec2 size, glm::vec4 bgColor, std::string text);
	void setPos(glm::vec2 pos);
	void setSize(glm::vec2 size);
	void setColor(glm::vec4 color);
private:
	glm::vec2 position;
	glm::vec2 size;
};