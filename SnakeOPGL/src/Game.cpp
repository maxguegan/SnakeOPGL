#include "Game.h"

Game::Game(const float width, const float height): width(width), height(height), state(ACTIVE), score(0){}
Tile::Tile(glm::vec2 position) :position(position), state(EMPTY){}
SpriteRenderer* renderer;
Player* player;
BonusItem* bonus;
TextRenderer* textRenderer;
UIText* scoreText;
UIText* pauseText;
UIText* gameOverText;
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
	player = new Player(tiles, tiles[0].size() / 2 - 3, tiles.size() / 2,Ressource::GetTexture("head"), Ressource::GetTexture("body"), Ressource::GetTexture("tail") ,glm::vec2(tileSize));
	bonus = new BonusItem(tiles,0,0,Ressource::GetTexture("bonus"),glm::vec2(0.0f),glm::vec2(tileSize));
	bonus->MoveBonus();
	textRenderer = new TextRenderer("../fonts/arial.ttf");
	
	scoreText = new  UIText("Score : 0", glm::vec2(25.0f, 500.0f), 1.0f, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), *textRenderer, Ressource::GetShader("TextShader"));
	
	glm::vec2 posTextMilieu = textRenderer->getSize("PAUSE") * 1.5f;
	posTextMilieu.x = (width - posTextMilieu.x) / 2;
	posTextMilieu.y = (height - posTextMilieu.y) / 2;
	pauseText = new  UIText("PAUSE", posTextMilieu, 1.5f, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), *textRenderer, Ressource::GetShader("TextShader"));
	posTextMilieu = textRenderer->getSize("GAME OVER") * 2.0f;
	posTextMilieu.x = (width - posTextMilieu.x) / 2;
	posTextMilieu.y = (height - posTextMilieu.y) / 2;
	gameOverText = new  UIText("GAME OVER", posTextMilieu, 2.0f, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), *textRenderer, Ressource::GetShader("TextShader"));
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
				if(bonus->effect == SPEED)
					player->effects.push_back(Effect(SPEED, 5.0f, 1));
				bonus->MoveBonus();;
				score += bonus->value;
				bonus->value += bonus->value / 5;
				scoreText->chaine = std::string("Score : ").append(std::to_string(score));
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
void Game::ProcessMouse(double cursorPosX, double cursorPosY) {
	if (keys[GLFW_MOUSE_BUTTON_LEFT] && !lockKeys[GLFW_MOUSE_BUTTON_LEFT]) {
		lockKeys[GLFW_MOUSE_BUTTON_LEFT] = true;
		std::cout << cursorPosX << " : " << cursorPosY << std::endl;
	}
		
	if (!keys[GLFW_MOUSE_BUTTON_LEFT])
		lockKeys[GLFW_MOUSE_BUTTON_LEFT] = false;

}
void Game::Restart() {
	player->GameOver(tiles[0].size() / 2 - 3, tiles.size() / 2);
	score = 0;
	state = ACTIVE;
	bonus->value = 100;
	//tiles[bonus->tilePosY][bonus->tilePosX].state = EMPTY;
	scoreText->chaine = std::string("Score : 0");
	bonus->MoveBonus();
}
void Game::Render() {
	player->Draw(*renderer);
	bonus->draw(*renderer);
	scoreText->Draw();
	if (state == PAUSE)
		pauseText->Draw();
	if (state == OVER)
		gameOverText->Draw();
}