#include "Game.h"

Game::Game(const float width, const float height): width(width), height(height), state(ACTIVE), score(0){}
Tile::Tile(glm::vec2 position) :position(position){}
SpriteRenderer* renderer;
Player* player;
BonusItem* bonus;
TextRenderer* ui;
std::string test;
void Game::Init() {
	
	InitMap();
	Ressource::LoadShader("../shader/SpriteShader.vs", NULL, "../shader/SpriteShader.fs","SpriteShader");
	Ressource::LoadShader("../shader/TextShader.vs", NULL, "../shader/TextShader.fs", "TextShader");
	Ressource::LoadTexture("../texture/snakeTail.png", true, "tail");
	Ressource::LoadTexture("../texture/snakeBody.png", true, "body");
	Ressource::LoadTexture("../texture/snakeHead.png", true, "head");
	Ressource::LoadTexture("../texture/bonus.png", true, "bonus");
	glm::mat4 projection = glm::ortho(0.0f, width, 0.0f, height,-1.0f,1.0f);
	Ressource::GetShader("SpriteShader").setMat4("projection", projection);
	Ressource::GetShader("TextShader").setMat4("projection", projection);
	renderer = new SpriteRenderer(Ressource::GetShader("SpriteShader"));
	player = new Player(Ressource::GetTexture("head"), Ressource::GetTexture("body"), Ressource::GetTexture("tail"), glm::ivec2(tiles[0].size()/2, tiles.size()/2),glm::vec2(tileSize), tiles);
	bonus = new BonusItem(Ressource::GetTexture("bonus"),glm::vec2(0.0f),glm::vec2(tileSize));
	ui = new TextRenderer("../fonts/arial.ttf");
	test = "Score : ";
	test.append(std::to_string(score));
	MoveBonus();
	player->effects.push_back(Effect(SPEED, 5.0f, 1));
	return;
}
void Game::InitMap() {
	const int nbCol = static_cast<int>(this->width / this->tileSize);
	const int nbRow = static_cast<int>(this->height / this->tileSize);
	float offsetX = (this->width - this->tileSize * static_cast<float>(nbCol)) / 2;
	float offsetY = (this->height - this->tileSize * static_cast<float>(nbRow)) / 2;
	for (int i = 0; i < nbRow; i++) {
		std::vector<Tile> row;
		for (int j = 0; j < nbCol; j++) {
			float posY = this->tileSize * i + offsetY;
			float posX = this->tileSize * j + offsetX;
			Tile newTile(glm::vec2(posX, posY));
			row.push_back(newTile);
		}
		tiles.push_back(row);
	}
}
void Game::Update(float deltaTime) {
	float speed = player->speed + (score/50); 
	if (Game::state == ACTIVE) {
		timer -= deltaTime * speed;
		player->update(deltaTime);
		if (timer <= 0.0f) {
			int resultMove = player->Move();
			timer = maxTimer;
			if (resultMove == -1)
				state = OVER;
			if (resultMove == 1) {
				MoveBonus();
				score += bonus->value;
				bonus->value += bonus->value / 5;
				test = "Score : ";
				test.append(std::to_string(score));
			}
				
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
		if (keys[GLFW_KEY_P] && !lockKeys[GLFW_KEY_P] && state != PAUSE) {
			lockKeys[GLFW_KEY_P] = true;
			state = PAUSE;
		}
		else if(keys[GLFW_KEY_P] && !lockKeys[GLFW_KEY_P] && state == PAUSE) {
			lockKeys[GLFW_KEY_P] = true;
			state = ACTIVE;
		}
		if (!keys[GLFW_KEY_P])
			lockKeys[GLFW_KEY_P] = false;
	}
	
	if (keys[GLFW_KEY_R] && !lockKeys[GLFW_KEY_R] && (state == PAUSE || state == OVER)) {
		lockKeys[GLFW_KEY_R] = true;
		Restart();
	}
	if (!keys[GLFW_KEY_R])
		lockKeys[GLFW_KEY_R] = false;
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
void Game::Restart() {
	player->GameOver(glm::ivec2(tiles[0].size() / 2 - 3, tiles.size() / 2));
	score = 0;
	state = ACTIVE;
	bonus->value = 100;
	test = "Score : ";
	test.append(std::to_string(score));
	MoveBonus();
}
void Game::Render() {
	player->Draw(*renderer);
	bonus->draw(*renderer);
	ui->DrawText(test.c_str(), 25.0f, 500.0f, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f), Ressource::GetShader("TextShader"));
	if(state == PAUSE)
		ui->DrawText("PAUSE", width / 2 - 150, height / 2, 2.0f, glm::vec3(1.0f, 1.0f, 0.0f), Ressource::GetShader("TextShader"));
	if (state == OVER)
		ui->DrawText("GAME OVER", width / 2 - 300, height / 2, 2.0f, glm::vec3(1.0f, 1.0f, 0.0f), Ressource::GetShader("TextShader"));
}