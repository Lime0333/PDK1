#ifndef Game_hpp
#define Game_hpp

#include"SDL.h"
#include"SDL_image.h"
//#include"AssetManager.h"

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
	static void directionChange(int newDirection);

	void handleEvents();
	void update();
	bool running() { return isRunning; };
	void render();
	void clean();


	
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	static AssetManager *assets;

	enum groupLabels : std::size_t {
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles
	};

private:
	int cnt=0;
	SDL_Window* window;
};





#endif /* Game_hpp */
