#pragma once

#include"../Game.hpp"
#include"ECS.h"
#include"Components.h"
#include"../AssetManager.h"

class KeyboardController :public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	
	int aniUD = 0,aniLR=0;
	
	

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {

		
		if(Game::unpaused){
			if (Game::event.type == SDL_KEYDOWN) {
				switch (Game::event.key.keysym.sym) {
				case SDLK_w:
					transform->velocity.y = -1;
					aniUD = 1;
					break;

				case SDLK_a:
					transform->velocity.x = -1;
					aniLR = 1;
					break;

				case SDLK_d:
					transform->velocity.x = 1;
					aniLR = 2;
					break;

				case SDLK_s:
					transform->velocity.y = 1;
					aniUD = 2;
					break;

				default:

					break;
				}
			}

			if (Game::event.type == SDL_KEYUP) {
				switch (Game::event.key.keysym.sym) {
				case SDLK_w:
					transform->velocity.y = 0;

					switch (Game::skin) {
					case 1:
						sprite->Play("IdleUP");
					case 2:
						sprite->Play("IdleUP2");
					}
					
					
					if (aniUD == 1) {
						aniUD = 0;
					}

					break;

				case SDLK_a:
					transform->velocity.x = 0;
					switch(Game::skin){
					case 1:
						sprite->Play("IdleL");

					case 2:
						sprite->Play("IdleL2");
					}


					if (aniLR == 1) {
						aniLR = 0;
					}

					break;

				case SDLK_d:
					transform->velocity.x = 0;
					switch(Game::skin){
					case 1:

						sprite->Play("Idle");
					
					case 2:
						sprite->Play("Idle2");

					}


					if (aniLR == 2) {
						aniLR = 0;
					}

					break;

				case SDLK_s:
					transform->velocity.y = 0;
					switch(Game::skin){
					case 1:

						sprite->Play("IdleDOWN");
					
					case 2:

						sprite->Play("IdleDOWN2");
					}
					if (aniUD == 2) {
						aniUD = 0;
					}
					break;

				case SDLK_LSHIFT:
					Game::spawnProjectile();
					break;
				case SDLK_r:
					if (Game::ammo < Game::MAXammo) {
						system("BAT\\reload.bat");
						Game::cooldown = 100;
						Game::ammo = 5;
					}
					break;
				case SDLK_m:
					system("BAT\\moai.bat");
				case SDLK_ESCAPE:
					Game::isRunning = false;
				default:

					break;
				}

			}
			//std::cout << aniUD<<"   "<<aniLR << std::endl;

			//0=right 1=left 2=up 3=down 4=right-up 5=right-down 6=left-up 7=left-down

			if (aniUD == 1) {
				if (aniLR == 0) {
					sprite->spriteFlip = SDL_FLIP_NONE;
					switch(Game::skin){
					case 1:
						sprite->Play("WalkUP");
					case 2:
						sprite->Play("WalkUP2");

					}
					Game::kierunek = 2;
				}
				else if (aniLR == 1) {
					//UL anim
					Game::kierunek = 6;
				}
				else if (aniLR == 2) {
					//UR anim
					Game::kierunek = 4;
				}
			}
			else if (aniUD == 2) {
				if (aniLR == 0) {
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
					switch (Game::skin) {
					case 1:
						sprite->Play("WalkDOWN2");
					}
					Game::kierunek = 3;
				}
				else if (aniLR == 1) {
					//DL anim
					Game::kierunek = 7;
				}
				else if (aniLR == 2) {
					//DR anim
					Game::kierunek = 5;
				}
			}
			else if (aniUD == 0) {
				if (aniLR == 1) {
					sprite->spriteFlip = SDL_FLIP_NONE;
					switch{
						sprite->Play("WalkL");
					}
					Game::kierunek = 1;
				}
				else if (aniLR == 2) {
					sprite->spriteFlip = SDL_FLIP_NONE;
					sprite->Play("Walk");
					Game::kierunek = 0;
				}
				else if (aniLR == 0) {

				}
			}



		}
		if (Game::unpaused == false) {
			transform->velocity.x = 0;
			transform->velocity.y = 0;
		}

	}
};
