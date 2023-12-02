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
auto& enemy(manager.addEntity());
auto& label(manager.addEntity());

//0=right 1=left 2=up 3=down 4=right-up 5=right-down 6=left-up 7=left-down
int Game::kierunek = 0;
int pozx,pozy;
int Game::HP = 100;
int Game::cooldown = 5;

const int Game::MAXammo = 5;
int Game::ammo = Game::MAXammo;
char ammoString[Game::MAXammo];
int cooldownVLC;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{

	//system("moai.bat");
	
	system("KillVLC.bat");
	system("init.bat");

	for (int i=0; i < MAXammo; i++) {
		ammoString[i] = char(177);
	}

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
	assets->AddTexture("enemy", "assets/characters/e1/eg1.png");


	assets->AddTexture("projectileR", "assets/bullet/bulletR.png");
	assets->AddTexture("projectileL", "assets/bullet/bulletL.png");
	assets->AddTexture("projectileU", "assets/bullet/bulletU.png");
	assets->AddTexture("projectileD", "assets/bullet/bulletD.png");

	assets->AddFont("goudysto", "assets/GOUDYSTO.TTF", 30);
	assets->AddFont("comic", "assets/comic.ttf", 30);
	

	map = new Map("terrain", 3, 32);

	map->Map::LoadMap("assets/bg/maps/map.map", 25, 20);

	//player.addComponent<TransformComponent>(4);
	player.addComponent<TransformComponent>(800.0f, 640.0f, 32, 32, 4);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	enemy.addComponent<TransformComponent>(900.0f, 640.0f, 32, 32, 4);
	enemy.addComponent<SpriteComponent>("enemy", true);
	//enemy.addComponent<KeyboardController>();
	enemy.addComponent<ColliderComponent>("enemy");
	enemy.addGroup(groupPlayers);

	SDL_Color white = { 255,255,255,255 };
	SDL_Color HP_red = { 220,20,60,150 };
	SDL_Color darkGreyGreen = { 91, 101, 51,150 };

	
	label.addComponent<UILabel>(10, 10, "Test String", "goudysto", HP_red);

}


auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

auto& enemies(manager.getGroup(Game::groupEnemies));

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

	if (cooldown > 0) {
		cooldown--;
	}
	//std::cout << cooldown << std::endl;

	if (cooldownVLC > 1000) {
		system("KillVLC.bat");
		cooldownVLC = 0;
	}
	cooldownVLC++;

	{

		int p = ammo;
		for (int i = 0; i < MAXammo; i++) {
			if (p > 0) {
				p--;
				ammoString[i] = char(177);
			}
			else {
				ammoString[i] = ' ';
			}
			
		}
		
	}

	//std::cout << ammo << std::endl;

	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	//std::cout << playerPos.x<<"      "<<playerPos.y << std::endl;

	std::stringstream ss;
	ss << "HP:  " << HP << '%'<<"                             "<< ammoString;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "goudysto");
	
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

	if(cooldown<=0 and ammo>0){

		
		
		ammo--;

		cooldown = 20;

		//0=right 1=left 2=up 3=down 4=right-up 5=right-down 6=left-up 7=left-down
		switch (kierunek) {

		case 0:
			Game::assets->CreateProjectile(Vector2D(pozx + 120, pozy + 95), Vector2D(2, 0), 200, 2, "projectileR", true);
			break;
		case 1:
			Game::assets->CreateProjectile(Vector2D(pozx - 15, pozy + 26), Vector2D(-2, 0), 200, 2, "projectileL", true);
			break;
		case 2:
			Game::assets->CreateProjectile(Vector2D(pozx + 95, pozy - 10), Vector2D(0, -2), 200, 2, "projectileU", false);
			break;
		case 3:
			Game::assets->CreateProjectile(Vector2D(pozx + 26, pozy + 120), Vector2D(0, 2), 200, 2, "projectileD", false);
			break;
		case 4:
			Game::assets->CreateProjectile(Vector2D(pozx + 120, pozy + 95), Vector2D(2, -2), 200, 2, "projectileR", true);
			break;
		case 5:
			Game::assets->CreateProjectile(Vector2D(pozx + 120, pozy + 95), Vector2D(2, 2), 200, 2, "projectileR", true);
			break;
		case 6:
			Game::assets->CreateProjectile(Vector2D(pozx - 15, pozy + 26), Vector2D(-2, -2), 200, 2, "projectileL", true);
			break;
		case 7:
			Game::assets->CreateProjectile(Vector2D(pozx - 15, pozy + 26), Vector2D(-2, 2), 200, 2, "projectileL", true);
			break;
		default:
			break;
		}
		system("gunShot.bat");
	}
	else if(ammo<=0) {
		system("noAmmo.bat");
	}
	
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

	for (auto& e : enemies) {
		e->draw();
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

