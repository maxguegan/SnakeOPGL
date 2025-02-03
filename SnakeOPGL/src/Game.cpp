#include "Game.h"

Game::Game(const float width, const float height): width(width), height(height){}
Tile::Tile(glm::vec2 position) :position(position){}
GAMESTATE Game::state = ACTIVE;
SpriteRenderer* renderer;
Player* player;
void Game::Init() {
	
	InitMap();
	Ressource::LoadShader("../shader/SpriteShader.vs", NULL, "../shader/SpriteShader.fs","SpriteShader");
	Ressource::LoadTexture("../texture/snakeBody.png", true, "body");
	glm::mat4 projection = glm::ortho(0.0f, width, 0.0f, height,-1.0f,1.0f);
	Ressource::GetShader("SpriteShader").setMat4("projection", projection);
	renderer = new SpriteRenderer(Ressource::GetShader("SpriteShader"));
	player = new Player(Ressource::GetTexture("body"), glm::ivec2(30, 10), tiles);
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
	float speed = 10.0f; 
	if (Game::state == ACTIVE) {
		timer -= deltaTime * speed;
		if (timer <= 0.0f) {
			player->Move();
			timer = maxTimer;
		}
	}
		
	
	
}

void Game::ProcessInput() {
	if (keys[GLFW_KEY_A] && player->curDir != DROITE)
		player->nextDir = GAUCHE;
	if (keys[GLFW_KEY_D] && player->curDir != GAUCHE)
		player->nextDir = DROITE;
	if (keys[GLFW_KEY_W] && player->curDir != BAS)
		player->nextDir = HAUT;
	if (keys[GLFW_KEY_S] && player->curDir != HAUT)
		player->nextDir = BAS;
}
void Game::Render() {
	player->Draw(*renderer);
}