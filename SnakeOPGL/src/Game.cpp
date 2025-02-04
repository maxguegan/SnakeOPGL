#include "Game.h"

Game::Game(const float width, const float height): width(width), height(height), state(ACTIVE){}
Tile::Tile(glm::vec2 position) :position(position){}
SpriteRenderer* renderer;
Player* player;
BonusItem* bonus;
bool toggleLock = false;
void Game::Init() {
	
	InitMap();
	Ressource::LoadShader("../shader/SpriteShader.vs", NULL, "../shader/SpriteShader.fs","SpriteShader");
	Ressource::LoadTexture("../texture/snakeTail.png", true, "tail");
	Ressource::LoadTexture("../texture/snakeBody.png", true, "body");
	Ressource::LoadTexture("../texture/snakeHead.png", true, "head");
	Ressource::LoadTexture("../texture/bonus.png", true, "bonus");
	glm::mat4 projection = glm::ortho(0.0f, width, 0.0f, height,-1.0f,1.0f);
	Ressource::GetShader("SpriteShader").setMat4("projection", projection);
	renderer = new SpriteRenderer(Ressource::GetShader("SpriteShader"));
	player = new Player(Ressource::GetTexture("head"), Ressource::GetTexture("body"), Ressource::GetTexture("tail"), glm::ivec2(tiles[0].size()/2, tiles.size()/2),glm::vec2(tileSize), tiles);
	bonus = new BonusItem(Ressource::GetTexture("bonus"),glm::vec2(0.0f),glm::vec2(tileSize));
	MoveBonus();
	return;
}
void Game::InitMap() {
	const int nbCol = static_cast<int>(this->width / this->tileSize);
	const int nbRow = static_cast<int>(this->height / this->tileSize);
	float offsetX = this->width - this->tileSize * static_cast<float>(nbCol);
	float offsetY = this->height - this->tileSize * static_cast<float>(nbRow);
	std::cout << " tile stat " << nbRow << ", " << nbCol << ", " << offsetX << ", " << offsetY << std::endl;
	for (int i = 0; i < nbRow; i++) {
		std::vector<Tile> row;
		for (int j = 0; j < nbCol; j++) {
			float posY = this->tileSize * i;
			float posX = this->tileSize * j;
			Tile newTile(glm::vec2(posX, posY));
			row.push_back(newTile);
		}
		tiles.push_back(row);
	}
}
void Game::Update(float deltaTime) {
	float speed = 20.0f; 
	if (Game::state == ACTIVE) {
		timer -= deltaTime * speed;
		if (timer <= 0.0f) {
			int resultMove = player->Move();
			timer = maxTimer;
			if (resultMove == -1)
				state = OVER;
			if (resultMove == 1)
				MoveBonus();
		}
	}
		
	
	
}

void Game::ProcessInput() {
	if (Game::state == ACTIVE || Game::state == PAUSE) {
		if (keys[GLFW_KEY_A] && player->curDir != DROITE)
			player->nextDir = GAUCHE;
		if (keys[GLFW_KEY_D] && player->curDir != GAUCHE)
			player->nextDir = DROITE;
		if (keys[GLFW_KEY_W] && player->curDir != BAS)
			player->nextDir = HAUT;
		if (keys[GLFW_KEY_S] && player->curDir != HAUT)
			player->nextDir = BAS;
		if (keys[GLFW_KEY_P] && !toggleLock && state != PAUSE) {
			toggleLock = true;
			state = PAUSE;
		}
		else if(keys[GLFW_KEY_P] && !toggleLock && state == PAUSE) {
			toggleLock = true;
			state = ACTIVE;
		}
		if (!keys[GLFW_KEY_P])
			toggleLock = false;
	}
	}
void Game::MoveBonus() {
	int newPosX;
	int newPosY;
	do {
		newPosX = std::rand() % tiles[0].size();
		newPosY = std::rand() % tiles.size();

	} while (tiles[newPosY][newPosX].state == SNAKE);
	tiles[newPosY][newPosX].state = BONUS;
	bonus->position = tiles[newPosY][newPosX].position;
}
void Game::Render() {
	player->Draw(*renderer);
	bonus->draw(*renderer);
}