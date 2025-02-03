#include "Player.h"

Player::Player(Texture& headTexture, glm::ivec2 pos, std::vector<std::vector<Tile>>& map)
	: headTexture(headTexture), headPos(pos),map(map), curDir(GAUCHE), nextDir(GAUCHE)
{

	for (int i = 0; i < STARTSIZE; i++) {
		this->body.push_back(GameObject(headTexture, map[headPos.y][headPos.x + i].position, glm::vec2(20.0f)));
	}
}

void Player::Draw(SpriteRenderer& renderer) {
	for(GameObject part : body)
		part.draw(renderer);
}

void Player::Move() {
	int limitY = map.size();
	int limitX = map[0].size();
	curDir = nextDir;
	switch (curDir)
	{
	case DROITE:
		if (headPos.x < limitX -1) {
			headPos.x += 1;
			updatePos();
		}
		break;
	case GAUCHE:
		if (headPos.x > 0) {
			headPos.x -= 1;
			updatePos();
		}
		break;
	case HAUT:
		if (headPos.y < limitY - 1) {
			headPos.y += 1;
			updatePos();
		}
		break;
	case BAS:
		if (headPos.y > 0) {
			headPos.y -= 1;
			updatePos();
		}
		break;
	default:
		break;
	}
}

void Player::updatePos() {
	for (int i = body.size(); i > 0; i--)
	{
		body[i].position = body[i - 1].position;
		
	}
	body[0].position = map[headPos.y][headPos.x].position;

}