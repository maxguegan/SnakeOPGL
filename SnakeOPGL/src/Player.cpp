#include "Player.h"

Player::Player(Texture& headTexture, Texture& bodyTexture, Texture& tailTexture, glm::ivec2 pos, glm::vec2 size, std::vector<std::vector<Tile>>& map)
	: headTexture(headTexture), bodyTexture(bodyTexture), tailTexture(tailTexture),headPos(pos),size(size), map(map), speed(BASESPEED), curDir(GAUCHE), nextDir(GAUCHE)
{
	Spawn(headPos);
	
}
void Player::Spawn(glm::ivec2 resPos) {
	body.clear();
	headPos = resPos;
	curDir = GAUCHE;
	nextDir = GAUCHE;
	for (int i = 0; i < STARTSIZE; i++) {
		if(resPos.x + i >= map[0].size()){}
		this->position[i] = glm::ivec2(resPos.x + i, resPos.y);
		map[resPos.y][resPos.x + i].state = SNAKE;
		this->body.push_back(GameObject(bodyTexture, map[resPos.y][resPos.x + i].position, size));
	}
	//assign correct texture
	body[0].sprite = headTexture;
	body[body.size() - 1].sprite = tailTexture;
}

void Player::update(float deltaTime) {
	if (effects.size() > 0) {
		std::vector<Effect>::iterator it;
		for (it = effects.begin(); it < effects.end(); it++) {
			switch ((*it).type) {
			case TRANSPARENT:
				break;
			case SPEED:
				speed = 30.0f;
				Ressource::GetShader("SpriteShader").setVec4("aColor", glm::vec4(1.0f, 0.5f, 0.5f, 1.0f));
				break;
			case POINT:
				break;
			}
			(*it).duration -= deltaTime;
			if ((*it).duration <= 0.0f)
			{
				speed = BASESPEED;
				Ressource::GetShader("SpriteShader").setVec4("aColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
				std::cout << "test" << std::endl;
				effects.erase(it);
				return;
			}
				
		}
	}
}
void Player::GameOver(glm::ivec2 resPos) {
	for (int i = 0; i < body.size(); i++)
		map[position[i].y][position[i].x].state = EMPTY;
	Spawn(resPos);
	
}
void Player::Draw(SpriteRenderer& renderer) {
	for(GameObject part : body)
		part.draw(renderer);
}

int Player::Move() {
	int limitY = map.size();
	int limitX = map[0].size();
	curDir = nextDir;
	switch (curDir)
	{
	case DROITE:
		if (headPos.x < limitX -1) {
			headPos.x += 1;
			body[0].rotation = 180.0f;
		}
		break;
	case GAUCHE:
		if (headPos.x > 0) {
			headPos.x -= 1;
			body[0].rotation = 0.0f;
		}
		break;
	case HAUT:
		if (headPos.y < limitY - 1) {
			headPos.y += 1;
			body[0].rotation = 270.0f;
		}
		break;
	case BAS:
		if (headPos.y > 0) {
			headPos.y -= 1;
			body[0].rotation = 90.0f;
		}
		break;
	default:
		break;
	}
	if (map[headPos.y][headPos.x].state == SNAKE)
		return -1;
	if (map[headPos.y][headPos.x].state == BONUS) {
		addSize();
		updatePos();
		return 1;
	}
	updatePos();

	return 0;
}
void Player::addSize() {
	int size = body.size();
	body[size - 1].sprite = bodyTexture;
	body.push_back(GameObject(tailTexture, body[size - 1].position, this->size));
	position[size] = position[size - 1];
}

void Player::updatePos() {
	map[position[body.size() - 1].y][position[body.size() - 1].x].state = EMPTY;
	for (int i = body.size() - 1; i > 0; i--)
	{
		position[i] = position[i - 1];
		body[i].position = body[i - 1].position;
		body[i].rotation = body[i - 1].rotation;
	}
	position[0] = glm::ivec2(headPos.x, headPos.y);
	body[0].position = map[headPos.y][headPos.x].position;
	map[headPos.y][headPos.x].state = SNAKE;
}