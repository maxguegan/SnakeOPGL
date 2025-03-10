#include "Button.h"
Button::Button(glm::vec2 pos, glm::vec2 size, glm::vec4 bgColor, std::string text, TextRenderer& renderer, Shader& shader) : position(pos), size(size) {
	backGround = new GameObject(Texture(), position, size, bgColor);
	float scaleText = size.x / renderer.getSize(text).x;

	if (scaleText > size.y / renderer.getSize(text).y)
		scaleText = size.y / renderer.getSize(text).y;
	float xOffSet = (size.x - renderer.getSize(text).x * scaleText) / 2;
	float yOffSet = (size.y - renderer.getSize(text).y * scaleText) / 2;
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