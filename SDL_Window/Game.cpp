#include "Game.hpp"

#include"TextureManager.h"
#include"Map.h"
#include "ECS/Components.h"
#include"Vector2D.h"
#include"Collision.h"
#include"AssetManager.h"
#include"ECS/Enemies/EnemiesComponent.h"

#include<sstream>


Map* map;
Manager manager;


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,800,640 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());

auto& enemy1(manager.addEntity());
auto& enemy2(manager.addEntity());
auto& enemy3(manager.addEntity());

auto& label(manager.addEntity());

//0=right 1=left 2=up 3=down 4=right-up 5=right-down 6=left-up 7=left-down
int Game::kierunek = 0;
int Game::pPosX; 
int Game::pPosY;
int Game::HP = 100;
int Game::cooldown = 5;

int Game::ePosX1;
int Game::ePosX2;
int Game::ePosX3;
int Game::ePosX4;
int Game::ePosX5;

int Game::ePosY1;
int Game::ePosY2;
int Game::ePosY3;
int Game::ePosY4;
int Game::ePosY5;

int Game::eHP1 = 100;
int Game::eHP2 = 100;
int Game::eHP3 = 100;
int Game::eHP4 = 100;
int Game::eHP5 = 100;

int Game::eCool1 = 500;
int Game::eCool2 = 500;
int Game::eCool3 = 500;
int Game::eCool4 = 500;
int Game::eCool5 = 500;

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
	
	system("BAT\\KillVLC.bat");
	//system("BAT\\init.bat");

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

	assets->AddTexture("enemy1", "assets/characters/e1/eg1.png");
	assets->AddTexture("enemy2", "assets/characters/e1/eg1.png");
	assets->AddTexture("enemy3", "assets/characters/e1/eg1.png");


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


	enemy1.addComponent<TransformComponent>(900.0f, 640.0f, 32, 32, 4);
	enemy1.addComponent<SpriteComponent>("enemy1", true);
	enemy1.addComponent<E1>();
	enemy1.addComponent<ColliderComponent>("enemy1");
	enemy1.addGroup(groupEnemies1);

	enemy2.addComponent<TransformComponent>(400.0f, 640.0f, 32, 32, 4);
	enemy2.addComponent<SpriteComponent>("enemy2", true);
	enemy2.addComponent<E2>();
	enemy2.addComponent<ColliderComponent>("enemy2");
	enemy2.addGroup(groupEnemies2);

	enemy3.addComponent<TransformComponent>(1000.0f, 440.0f, 32, 32, 4);
	enemy3.addComponent<SpriteComponent>("enemy3", true);
	enemy3.addComponent<E3>();
	enemy3.addComponent<ColliderComponent>("enemy3");
	enemy3.addGroup(groupEnemies3);


	SDL_Color white = { 255,255,255,255 };
	SDL_Color HP_red = { 220,20,60,150 };
	SDL_Color darkGreyGreen = { 91, 101, 51,150 };

	
	label.addComponent<UILabel>(10, 10, "Test String", "goudysto", HP_red);

}
/*
void Game::killEnemy() {
	enemy.delGroup(groupEnemies);
}
*/
auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

auto& enemies1(manager.getGroup(Game::groupEnemies1));
auto& enemies2(manager.getGroup(Game::groupEnemies2));
auto& enemies3(manager.getGroup(Game::groupEnemies3));

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

	eCool1--;
	eCool2--;
	eCool3--;
	eCool4--;
	eCool5--;

	//std::cout << cooldown << std::endl;

	if (cooldownVLC > 1000) {
		system("BAT\\KillVLC.bat");
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

	pPosX = playerPos.x;
	pPosY = playerPos.y;




	SDL_Rect enemy1Col = enemy1.getComponent<ColliderComponent>().collider;
	Vector2D enemy1Pos = enemy1.getComponent<TransformComponent>().position;

	ePosX1 = enemy1Pos.x;
	ePosY1 = enemy1Pos.y;

	SDL_Rect enemy2Col = enemy2.getComponent<ColliderComponent>().collider;
	Vector2D enemy2Pos = enemy2.getComponent<TransformComponent>().position;

	ePosX2 = enemy2Pos.x;
	ePosY2 = enemy2Pos.y;

	SDL_Rect enemy3Col = enemy3.getComponent<ColliderComponent>().collider;
	Vector2D enemy3Pos = enemy3.getComponent<TransformComponent>().position;

	ePosX3 = enemy3Pos.x;
	ePosY3 = enemy3Pos.y;




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
			//std::cout << "Hit player" << std::endl;
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
}

void Game::spawnProjectile() {
	if(cooldown<=0 and ammo>0){
		ammo--;

		cooldown = 20;

		//0=right 1=left 2=up 3=down 4=right-up 5=right-down 6=left-up 7=left-down
		switch (kierunek) {

		case 0:
			Game::assets->CreateProjectile(Vector2D(pPosX + 120, pPosY + 95), Vector2D(2, 0), 200, 2, "projectileR", true, 0);
			break;
		case 1:
			Game::assets->CreateProjectile(Vector2D(pPosX - 15, pPosY + 26), Vector2D(-2, 0), 200, 2, "projectileL", true, 0);
			break;
		case 2:
			Game::assets->CreateProjectile(Vector2D(pPosX + 95, pPosY - 10), Vector2D(0, -2), 200, 2, "projectileU", false, 0);
			break;
		case 3:
			Game::assets->CreateProjectile(Vector2D(pPosX + 26, pPosY + 120), Vector2D(0, 2), 200, 2, "projectileD", false, 0);
			break;
		case 4:
			Game::assets->CreateProjectile(Vector2D(pPosX + 120, pPosY + 95), Vector2D(2, -2), 200, 2, "projectileR", true, 0);
			break;
		case 5:
			Game::assets->CreateProjectile(Vector2D(pPosX + 120, pPosY + 95), Vector2D(2, 2), 200, 2, "projectileR", true, 0);
			break;
		case 6:
			Game::assets->CreateProjectile(Vector2D(pPosX - 15, pPosY + 26), Vector2D(-2, -2), 200, 2, "projectileL", true, 0);
			break;
		case 7:
			Game::assets->CreateProjectile(Vector2D(pPosX - 15, pPosY + 26), Vector2D(-2, 2), 200, 2, "projectileL", true, 0);
			break;
		default:
			break;
		}
		system("BAT\\gunShot.bat");
	}
	else if(ammo<=0) {
		system("BAT\\noAmmo.bat");
	}
	
}

void Game::ESpawnP(int Eid, int kierunek) {
	

	switch (Eid) {
	case 1:
		
		switch (kierunek) {

		case 0:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX1 + 120, Game::ePosY1 + 95), Vector2D(2, 0), 200, 2, "projectileR", true, Eid);
			break;
		case 1:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX1 - 15, Game::ePosY1 + 26), Vector2D(-2, 0), 200, 2, "projectileL", true, Eid);
			break;
		case 2:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX1 + 95, Game::ePosY1 - 10), Vector2D(0, -2), 200, 2, "projectileU", false, Eid);
			break;
		case 3:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX1 + 26, Game::ePosY1 + 120), Vector2D(0, 2), 200, 2, "projectileD", false, Eid);
			break;
		case 4:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX1 + 120, Game::ePosY1 + 95), Vector2D(2, -2), 200, 2, "projectileR", true, Eid);
			break;
		case 5:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX1 + 120, Game::ePosY1 + 95), Vector2D(2, 2), 200, 2, "projectileR", true, Eid);
			break;
		case 6:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX1 - 15, Game::ePosY1 + 26), Vector2D(-2, -2), 200, 2, "projectileL", true, Eid);
			break;
		case 7:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX1 - 15, Game::ePosY1 + 26), Vector2D(-2, 2), 200, 2, "projectileL", true, Eid);
			break;
		default:
			break;
		}

		eCool1 = 410;

		break;
	case 2:
		
		switch (kierunek) {

		case 0:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX2 + 120, Game::ePosY2 + 95), Vector2D(2, 0), 200, 2, "projectileR", true, Eid);
			break;
		case 1:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX2 - 15, Game::ePosY2 + 26), Vector2D(-2, 0), 200, 2, "projectileL", true, Eid);
			break;
		case 2:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX2 + 95, Game::ePosY2 - 10), Vector2D(0, -2), 200, 2, "projectileU", false, Eid);
			break;
		case 3:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX2 + 26, Game::ePosY2 + 120), Vector2D(0, 2), 200, 2, "projectileD", false, Eid);
			break;
		case 4:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX2 + 120, Game::ePosY2 + 95), Vector2D(2, -2), 200, 2, "projectileR", true, Eid);
			break;
		case 5:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX2 + 120, Game::ePosY2 + 95), Vector2D(2, 2), 200, 2, "projectileR", true, Eid);
			break;
		case 6:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX2 - 15, Game::ePosY2 + 26), Vector2D(-2, -2), 200, 2, "projectileL", true, Eid);
			break;
		case 7:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX2 - 15, Game::ePosY2 + 26), Vector2D(-2, 2), 200, 2, "projectileL", true, Eid);
			break;
		default:
			break;
		}

		eCool2 = 420;

		break;
	case 3:
		
		switch (kierunek) {

		case 0:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX3 + 120, Game::ePosY3 + 95), Vector2D(2, 0), 200, 2, "projectileR", true, Eid);
			break;
		case 1:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX3 - 15, Game::ePosY3 + 26), Vector2D(-2, 0), 200, 2, "projectileL", true, Eid);
			break;
		case 2:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX3 + 95, Game::ePosY3 - 10), Vector2D(0, -2), 200, 2, "projectileU", false, Eid);
			break;
		case 3:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX3 + 26, Game::ePosY3 + 120), Vector2D(0, 2), 200, 2, "projectileD", false, Eid);
			break;
		case 4:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX3 + 120, Game::ePosY3 + 95), Vector2D(2, -2), 200, 2, "projectileR", true, Eid);
			break;
		case 5:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX3 + 120, Game::ePosY3 + 95), Vector2D(2, 2), 200, 2, "projectileR", true, Eid);
			break;
		case 6:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX3 - 15, Game::ePosY3 + 26), Vector2D(-2, -2), 200, 2, "projectileL", true, Eid);
			break;
		case 7:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX3 - 15, Game::ePosY3 + 26), Vector2D(-2, 2), 200, 2, "projectileL", true, Eid);
			break;
		default:
			break;
		}

		eCool3 = 430;

		break;
	case 4:
		
		switch (kierunek) {

		case 0:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX4 + 120, Game::ePosY4 + 95), Vector2D(2, 0), 200, 2, "projectileR", true, Eid);
			break;
		case 1:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX4 - 15, Game::ePosY4 + 26), Vector2D(-2, 0), 200, 2, "projectileL", true, Eid);
			break;
		case 2:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX4 + 95, Game::ePosY4 - 10), Vector2D(0, -2), 200, 2, "projectileU", false, Eid);
			break;
		case 3:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX4 + 26, Game::ePosY4 + 120), Vector2D(0, 2), 200, 2, "projectileD", false, Eid);
			break;
		case 4:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX4 + 120, Game::ePosY4 + 95), Vector2D(2, -2), 200, 2, "projectileR", true, Eid);
			break;
		case 5:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX4 + 120, Game::ePosY4 + 95), Vector2D(2, 2), 200, 2, "projectileR", true, Eid);
			break;
		case 6:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX4 - 15, Game::ePosY4 + 26), Vector2D(-2, -2), 200, 2, "projectileL", true, Eid);
			break;
		case 7:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX4 - 15, Game::ePosY4 + 26), Vector2D(-2, 2), 200, 2, "projectileL", true, Eid);
			break;
		default:
			break;
		}

		eCool4 = 440;

		break;
	case 5:
		
		switch (kierunek) {

		case 0:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX5 + 120, Game::ePosY5 + 95), Vector2D(2, 0), 200, 2, "projectileR", true, Eid);
			break;
		case 1:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX5 - 15, Game::ePosY5 + 26), Vector2D(-2, 0), 200, 2, "projectileL", true, Eid);
			break;
		case 2:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX5 + 95, Game::ePosY5 - 10), Vector2D(0, -2), 200, 2, "projectileU", false, Eid);
			break;
		case 3:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX5 + 26, Game::ePosY5 + 120), Vector2D(0, 2), 200, 2, "projectileD", false, Eid);
			break;
		case 4:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX5 + 120, Game::ePosY5 + 95), Vector2D(2, -2), 200, 2, "projectileR", true, Eid);
			break;
		case 5:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX5 + 120, Game::ePosY5 + 95), Vector2D(2, 2), 200, 2, "projectileR", true, Eid);
			break;
		case 6:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX5 - 15, Game::ePosY5 + 26), Vector2D(-2, -2), 200, 2, "projectileL", true, Eid);
			break;
		case 7:
			Game::assets->CreateProjectile(Vector2D(Game::ePosX5 - 15, Game::ePosY5 + 26), Vector2D(-2, 2), 200, 2, "projectileL", true, Eid);
			break;
		default:
			break;
		}

		eCool5 = 400;

		break;
	}

	system("Bat\\EGunShot.bat");

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
	
	for (auto& e : enemies1) {
		e->draw();
	}
	for (auto& e : enemies3) {
		e->draw();
	}
	for (auto& e : enemies2) {
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

