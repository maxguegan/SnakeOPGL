#include "Button.h"
Button::Button(glm::vec2 pos, glm::vec2 size, glm::vec4 bgColor, std::string text, TextRenderer& renderer, Shader& shader) : position(pos), size(size) {
	backGround = new GameObject(Texture(), position, size, bgColor);
	
	glm::vec3 textSize = renderer.getSize(text);
	float scaleText = size.x / textSize.x;
	if (scaleText > size.y / (textSize.y + textSize.z))
		scaleText = size.y / (textSize.y + textSize.z);
	float xOffSet = (size.x - textSize.x * scaleText) / 2;
	float yOffSet = (size.y - (textSize.y + textSize.z) * scaleText) / 2 + textSize.y;
	pos.x += xOffSet;
	pos.y += yOffSet;
	 buttonText = new UIText(text, pos, scaleText, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), renderer, shader);
}

Button::~Button() {
	free(backGround);
	free(buttonText);
}

void Button::Draw(SpriteRenderer& spriteRenderer) {
	
	buttonText->Draw();
	Ressource::GetShader("SpriteShader").setBool("useTexture", false);
	backGround->draw(spriteRenderer);
	
}
bool Button::OnClick(float posX, float posY) {
	
	return (posX >= position.x && posX <= position.x + size.x && posY >= position.y && posY <= position.y + size.y);
}