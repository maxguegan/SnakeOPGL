#pragma once
#include <glm/glm.hpp>
#include <string>
#include "GameObject.h"
#include "UIText.h"
#include "Ressource.h"

class Button {

public:
	UIText * buttonText;
	GameObject * backGround;
	Button(glm::vec2 pos, glm::vec2 size, glm::vec4 bgColor, std::string text, TextRenderer& renderer, Shader& shader);
	~Button();
	void setPos(glm::vec2 pos);
	void setSize(glm::vec2 size);
	void Draw(SpriteRenderer& spriteRenderer);
	bool OnClick(float posX,float posY);
private:
	glm::vec2 position;
	glm::vec2 size;
};