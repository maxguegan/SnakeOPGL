#pragma once
#include <string>
#include <glm/glm.hpp>
#include "TextRenderer.h"
#include "Shader.h"

class UIText {
public:



	float scale;

	std::string chaine;
	glm::vec2 position;
	glm::vec4 color;
	TextRenderer& textRenderer;
	Shader& shader;

	UIText(std::string chaine, glm::vec2 position, float scale, glm::vec4 color, TextRenderer& textRenderer, Shader& shader);
	void Draw();
};
