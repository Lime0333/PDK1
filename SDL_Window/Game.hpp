#ifndef Game_hpp
#define Game_hpp

#include"SDL.h"
#include"SDL_image.h"

#include<iostream>
#include<vector>

#undef main

class ColliderComponent;
class AssetManager;

class Game {

public:

	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	static void spawnProjectile();
	static void ESpawnP(int Eid,int kierunek);	

	void handleEvents();
	void update();
	bool running() { return isRunning; };
	void render();
	void clean();


	static bool unpaused;
	
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	static AssetManager *assets;

	static int cooldown;
	static int kierunek;
	static int HP;
	static int skin;
	
	static int ammo;
	static const int MAXammo;
	
	static int ePosX1;
	static int ePosX2;
	static int ePosX3;
	static int ePosX4;
	static int ePosX5;
	static int NPCPosX1;
	static int NPCPosX2;
	static int NPCPosX3;

	static int ePosY1;
	static int ePosY2;
	static int ePosY3;
	static int ePosY4;
	static int ePosY5;
	static int NPCPosY1;
	static int NPCPosY2;
	static int NPCPosY3;

	static int eHP1;
	static int eHP2;
	static int eHP3;
	static int eHP4;
	static int eHP5;

	static int eCool1;
	static int eCool2;
	static int eCool3;
	static int eCool4;
	static int eCool5;

	static int pPosX;
	static int pPosY;


	static float FlashPosX;
	static float FlashPosY;

	static int pCenterX;
	static int pCenterY;


	enum groupLabels : std::size_t {
		groupMap,
		groupPlayers,

		groupFlashlight,

		groupEnemies1,
		groupEnemies2,
		groupEnemies3,

		groupNPC1,
		groupNPC2,
		groupNPC3,
		
		groupColliders,
		groupProjectiles
	};

private:
	int cnt=0;
	SDL_Window* window;
};





#endif /* Game_hpp */
