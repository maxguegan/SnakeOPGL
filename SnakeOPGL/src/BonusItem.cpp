#include "BonusItem.h"
BonusItem::BonusItem(std::vector<std::vector<Tile>>& map, int x, int y, Texture tex, glm::vec2 pos, glm::vec2 size, int val, glm::vec4 col, float rotate):TileObject(map, x, y, tex, size,col,rotate) {
	value = val;
	}
void BonusItem::MoveBonus() {
	int newPosX;
	int newPosY;
	int randBonus = std::rand() % 100;
	if (randBonus > 80)
		effect = SPEED;
	else 
		effect = NONE;
	do {
		newPosX = std::rand() % map[0].size();
		newPosY = std::rand() % map.size();

	} while (map[newPosY][newPosX].state == SNAKE);
	map[newPosY][newPosX].state = BONUS;
	this->setPos(newPosX, newPosY);
}
void BonusItem::draw(SpriteRenderer& renderer) {
	Ressource::GetShader("SpriteShader").setBool("useTexture", true);
	if (effect == SPEED) {
		Ressource::GetShader("SpriteShader").setBool("buffed", true);
		this->color = glm::vec4(1.0f, 0.5f, 0.0f, 1.0f);
	}
	else {
		Ressource::GetShader("SpriteShader").setBool("buffed", false);
	}
	

	GameObject::draw(renderer);
	Ressource::GetShader("SpriteShader").setBool("buffed", false);
}