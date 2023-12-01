#include "Game.hpp"

#include"TextureManager.h"
#include"Map.h"
#include "ECS/Components.h"
#include"Vector2D.h"
#include"Collision.h"
#include"AssetManager.h"
#include<sstream>

Map* map;
Manager manager;


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,800,640 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& label(manager.addEntity());

int pozx,pozy,direction=0;
//0=right 1=left 2=up 3=down

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{

	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialized!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	else { isRunning = false; }

	if (TTF_Init() == -1) {
		std::cout << "ERROR : SLD_TTF" << std::endl;
	}

	assets->AddTexture("terrain", "assets/bg/terrain_ss.png");
	assets->AddTexture("player", "assets/characters/ch1/ch1,2.png");
	assets->AddTexture("playerUP", "assets/characters/ch1/ch1UP.png");

	assets->AddTexture("projectileR", "assets/bullet/bulletR.png");
	assets->AddTexture("projectileL", "assets/bullet/bulletL.png");
	assets->AddTexture("projectileU", "assets/bullet/bulletU.png");
	assets->AddTexture("projectileD", "assets/bullet/bulletD.png");

	assets->AddFont("comic", "assets/comic.ttf", 16);

	map = new Map("terrain", 3, 32);

	map->Map::LoadMap("assets/bg/maps/map.map", 25, 20);

	//player.addComponent<TransformComponent>(4);
	player.addComponent<TransformComponent>(800.0f, 640.0f, 32, 32, 4);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	SDL_Color white = { 255,255,255,255 };

	label.addComponent<UILabel>(10, 10, "Test String", "comic", white);

}


auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

void Game::handleEvents() {

	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}



void Game::update() {

	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	std::cout << playerPos.x<<"      "<<playerPos.y << std::endl;

	std::stringstream ss;
	ss << "Player position: " << playerPos;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "comic");

	manager.refresh();
	manager.update();

	for (auto& c : colliders) {
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol)) {
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	for (auto& p : projectiles) {
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider)) {
			std::cout << "Hit player" << std::endl;
			//p->destroy();
		}
	}

	camera.x = player.getComponent<TransformComponent>().position.x - 350;
	camera.y = player.getComponent<TransformComponent>().position.y - 250;

	if (camera.x < 0) {
		camera.x = 0;
	}
	if (camera.y<0) {
		camera.y = 0;
	}
	if (camera.x > camera.w) {
		camera.x = camera.w;
	}
	if (camera.y > camera.h) {
		camera.y = camera.h;
	}


	pozx = playerPos.x;
	pozy = playerPos.y;
}

void Game::spawnProjectile() {
	switch (direction){
	case 0:
		Game::assets->CreateProjectile(Vector2D(pozx + 120, pozy + 95), Vector2D(2, 0), 200, 2, "projectileR",true);
		break;
	case 1:
		Game::assets->CreateProjectile(Vector2D(pozx - 20, pozy + 95), Vector2D(-2, 0), 200, 2, "projectileL",true);
		break;
	case 2:
		Game::assets->CreateProjectile(Vector2D(pozx + 95, pozy - 10), Vector2D(0, -2), 200, 2, "projectileU",false);
		break;
	case 3:
		Game::assets->CreateProjectile(Vector2D(pozx + 26, pozy + 120), Vector2D(0, 2), 200, 2, "projectileD", false);
		break;
	default:
		break;
	}
}

void Game::directionChange(int newDirection) {
	//0=right 1=left 2=up 3=down

	direction = newDirection;

}


void Game::render()
{
	
	SDL_RenderClear(renderer);
	for (auto& t : tiles) {
		t->draw();
	}
	
	for (auto& c : colliders) {
		c->draw();
	}
	
	for (auto& t : players) {
		t->draw();
	}

	//enemies usuniete
	
	for (auto& p : projectiles) {
		p->draw();
	}

	label.draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned!" << std::endl;
}

