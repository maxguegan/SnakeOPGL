#include "Player.h"

Player::Player(Texture& headTexture, glm::ivec2 pos, std::vector<std::vector<Tile>>& map)
	: headTexture(headTexture), headPos(pos),map(map), curDir(GAUCHE), nextDir(GAUCHE)
{

	for (int i = 0; i < STARTSIZE + 1; i++) {
		this->position[i] = glm::ivec2(headPos.x + i, headPos.y);
		map[headPos.y][headPos.x + i].state = SNAKE;
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
			
		}
		break;
	case GAUCHE:
		if (headPos.x > 0) {
			headPos.x -= 1;
			
		}
		break;
	case HAUT:
		if (headPos.y < limitY - 1) {
			headPos.y += 1;
			
		}
		break;
	case BAS:
		if (headPos.y > 0) {
			headPos.y -= 1;
			
		}
		break;
	default:
		break;
	}
	if (map[headPos.y][headPos.x].state == SNAKE)
		Game::state = OVER;
	updatePos();
}

void Player::updatePos() {
	map[position[body.size() - 1].y][position[body.size() - 1].x].state = EMPTY;
	for (int i = body.size() - 1; i > 0; i--)
	{
		position[i] = position[i - 1];
		body[i].position = body[i - 1].position;
		
	}
	position[0] = glm::ivec2(headPos.x, headPos.y);
	body[0].position = map[headPos.y][headPos.x].position;
	map[headPos.y][headPos.x].state = SNAKE;
}