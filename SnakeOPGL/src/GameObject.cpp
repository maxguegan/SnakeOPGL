#include "GameObject.h"

GameObject::GameObject(): position(glm::vec2(0.0f)), size(glm::vec2(1.0f)), sprite(),rotation(0.0f), color(glm::vec4(1.0f)) {

}
GameObject::GameObject(Texture tex, glm::vec2 position, glm::vec2 size,  glm::vec4 color,  float rotation): position(position), size(size), sprite(tex), rotation(rotation), color(color)
{

}

void GameObject::draw(SpriteRenderer & renderer) {
	
		renderer.Render(this->sprite, this->position, this->size, this->rotation, this->color);
}

GameObject::~GameObject(){}