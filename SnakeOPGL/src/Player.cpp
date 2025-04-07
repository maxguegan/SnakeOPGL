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
		Ressource::GetShader("SpriteShader").setBool("buffed", true);
		std::vector<Effect>::iterator it;
		for (it = effects.begin(); it < effects.end(); it++) {
			
			(*it).duration -= deltaTime;
			if ((*it).duration <= 1.0f) {
				blinkTimer -= deltaTime;
				if (blinkTimer < 0) {
					toggleVisible();
					blinkTimer = BLINK;
				}
				
			}

			if ((*it).duration <= 0.0f)
			{
				if ((*it).type == SPEED) {
					speed = BASESPEED;
				}
				else if ((*it).type == TRANSPARENT) {
					transparent = false;
				}
				
				effects.erase(it);
				setVisible(true);
			}
				
		}
	}else
		Ressource::GetShader("SpriteShader").setBool("buffed", false);
}
void Player::addBuff(Effect buff) {
	switch (buff.type) {
	case TRANSPARENT:
		transparent = true;
		for (Effect& effet : effects)
			if (effet.type == TRANSPARENT) {
				effet.duration += buff.duration;
				return;
			}
		setColor(transparentColor);
		break;
	case SPEED:
		for (Effect& effet : effects)
			if (effet.type == SPEED) {
				effet.duration += buff.duration;
				return;
			}
		speed = 30.0f;
		setColor(speedColor);
		break;
	case POINT:
		break;
	}
	effects.push_back(buff);
}
void Player::GameOver(int restartTilePosX, int restartTilePosY) {
	for(TileObject part : body)
		map[part.tilePosY][part.tilePosX].state = EMPTY;
	effects.clear();
	Spawn(restartTilePosX, restartTilePosY);
	
}
void Player::Draw(SpriteRenderer& renderer) {
	Ressource::GetShader("SpriteShader").setBool("useTexture", true);
	for(GameObject & part : body)
		part.draw(renderer);
	Ressource::GetShader("SpriteShader").setBool("buffed", false);
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
	if (map[headTilePosY][headTilePosX].state == SNAKE && !transparent)
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
	body.push_back(TileObject(map, body[size - 1].tilePosX, body[size - 1].tilePosY,tailTexture, this->size,this->baseColor));
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
void Player::setColor(glm::vec4 color) {
	this->baseColor = color;
	for (GameObject& parts : body)
		parts.color = color;
}
void Player::toggleVisible() {
	
	for (GameObject& parts : body)
		parts.visible = !parts.visible;
}
void Player::setVisible(bool visible) {

	for (GameObject& parts : body)
		parts.visible = visible;
}