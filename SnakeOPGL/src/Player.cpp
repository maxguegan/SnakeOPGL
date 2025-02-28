#include "Player.h"

Player::Player(std::vector<std::vector<Tile>>& map, int startTilePosX, int startTilePosY, Texture& headTexture, Texture& bodyTexture, Texture& tailTexture, glm::vec2 size)
	: headTexture(headTexture), bodyTexture(bodyTexture), tailTexture(tailTexture), size(size), map(map), speed(BASESPEED), curDir(GAUCHE), nextDir(GAUCHE)
{
	Spawn(startTilePosX, startTilePosY);
	
}
void Player::Spawn(int StartTilePosX, int StartTilePosY) {
	body.clear();
	curDir = GAUCHE;
	nextDir = GAUCHE;
	for (int i = 0; i < STARTSIZE; i++) {
		//todo gestion de spawn au limite 
		if(StartTilePosX + i >= map[0].size()){}
		map[StartTilePosY][StartTilePosX + i].state = SNAKE;
		this->body.push_back(TileObject(map, StartTilePosX + i, StartTilePosY,bodyTexture, size));
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
				Ressource::GetShader("SpriteShader").setBool("buffed", true);
				Ressource::GetShader("SpriteShader").setVec4("aColor", glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
				break;
			case POINT:
				break;
			}
			(*it).duration -= deltaTime;
			if ((*it).duration <= 0.0f)
			{
				Ressource::GetShader("SpriteShader").setBool("buffed", false);
				speed = BASESPEED;
				Ressource::GetShader("SpriteShader").setVec4("aColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
				std::cout << "test" << std::endl;
				effects.erase(it);
				return;
			}
				
		}
	}
}
void Player::GameOver(int restartTilePosX, int restartTilePosY) {
	for(TileObject part : body)
		map[part.tilePosY][part.tilePosX].state = EMPTY;
	Spawn(restartTilePosX, restartTilePosY);
	
}
void Player::Draw(SpriteRenderer& renderer) {
	for(GameObject part : body)
		part.draw(renderer);
}

int Player::Move() {
	int limitY = map.size();
	int limitX = map[0].size();
	int headTilePosX = body[0].tilePosX;
	int headTilePosY = body[0].tilePosY;
	curDir = nextDir;
	switch (curDir)
	{
	case DROITE:
		if (headTilePosX < limitX - 1) {
			headTilePosX += 1;
			body[0].rotation = 180.0f;
		}
		break;
	case GAUCHE:
		if (headTilePosX > 0) {
			headTilePosX -= 1;
			body[0].rotation = 0.0f;
		}
		break;
	case HAUT:
		if (headTilePosY < limitY - 1) {
			headTilePosY += 1;
			body[0].rotation = 270.0f;
		}
		break;
	case BAS:
		if (headTilePosY > 0) {
			headTilePosY -= 1;
			body[0].rotation = 90.0f;
		}
		break;
	default:
		break;
	}
	if (map[headTilePosY][headTilePosX].state == SNAKE)
		return -1;
	if (map[headTilePosY][headTilePosX].state == BONUS) {
		addSize();
		updatePos(headTilePosX, headTilePosY);
		return 1;
	}
	updatePos(headTilePosX, headTilePosY);

	return 0;
}
void Player::addSize() {
	int size = body.size();
	body[size - 1].sprite = bodyTexture;
	body.push_back(TileObject(map, body[size - 1].tilePosX, body[size - 1].tilePosY,tailTexture, this->size));
}

void Player::updatePos(int headTilePosX, int headTilePosY) {
	map[body[body.size() - 1].tilePosY][body[body.size() - 1].tilePosX].state = EMPTY;
	for (int i = body.size() - 1; i > 0; i--)
	{
		body[i].setPos(body[i - 1].tilePosX, body[i - 1].tilePosY);
		body[i].rotation = body[i - 1].rotation;
	}
	body[0].setPos(headTilePosX,headTilePosY);
	map[headTilePosY][headTilePosX].state = SNAKE;
}