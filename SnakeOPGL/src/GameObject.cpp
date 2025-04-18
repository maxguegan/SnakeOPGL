#include "GameObject.h"


GameObject::GameObject(Texture tex, glm::vec2 position, glm::vec2 size,  glm::vec4 color,  float rotation): position(position), size(size), sprite(tex), rotation(rotation), color(color)
{

}

void GameObject::draw(SpriteRenderer & renderer) {
	if(visible)
		renderer.Render(this->sprite, this->position, this->size, this->rotation, this->color);
}

GameObject::~GameObject(){}