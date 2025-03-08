#include "UIText.h"

UIText::UIText(std::string chaine, glm::vec2 position, float scale, glm::vec4 color, TextRenderer& textRenderer, Shader& shader)
	: chaine(chaine), position(position), scale(scale), color(color), textRenderer(textRenderer),shader(shader){}

void UIText::Draw() {
	textRenderer.DrawText(chaine, position.x, position.y, scale, glm::vec3(color.x, color.y, color.z), shader);
}