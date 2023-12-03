#pragma once


#include"../Game.hpp"
#include"ECS.h"
#include"Components.h"
#include"../AssetManager.h"

class EnemyMovement :public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	int aniUD = 0, aniLR = 0;
	bool alive=true;


	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		if (Game::eHP <= 0 and alive) {
			for (float i = 30; i > 0; i=i-10) {
				transform->velocity.y = i;
			}
			

			alive = false;
		}

		if (alive){
				
				//transform->velocity.y = -1;

				std::cout << Game::ePosX <<"   " << Game::ePosY << std::endl;

				if (Game::ePosX > Game::pPosX+10) {
					transform->velocity.x = -0.5;
					aniLR = 1;
				}
				else if (Game::ePosX < Game::pPosX - 10) {
					transform->velocity.x = 0.5;
					aniLR = 2;
				}
				else {

					transform->velocity.x = 0;
					aniLR = 0;
					sprite->Play("Idle");
				}
				if (Game::ePosY > Game::pPosY + 10) {
					transform->velocity.y = -0.5;
					aniUD = 1;
				}
				else if (Game::ePosY < Game::pPosY - 10) {
					transform->velocity.y = 0.5;
					aniUD = 2;
				}
				else {
					transform->velocity.y = 0;
					aniUD = 0;
					sprite->Play("IdleUP");
				}

				//std::cout << aniUD<<"   "<<aniLR << std::endl;

				//0=right 1=left 2=up 3=down 4=right-up 5=right-down 6=left-up 7=left-down

				if (aniUD == 1) {
					if (aniLR == 0) {
						sprite->spriteFlip = SDL_FLIP_NONE;
						sprite->Play("WalkUP");
						//Game::kierunek = 2;
					}
					else if (aniLR == 1) {
						//UL anim
						//Game::kierunek = 6;
					}
					else if (aniLR == 2) {
						//UR anim
						//Game::kierunek = 4;
					}
				}
				else if (aniUD == 2) {
					if (aniLR == 0) {
						sprite->spriteFlip = SDL_FLIP_NONE;
						sprite->Play("WalkDOWN");
						//Game::kierunek = 3;
					}
					else if (aniLR == 1) {
						//DL anim
						//Game::kierunek = 7;
					}
					else if (aniLR == 2) {
						//DR anim
						//Game::kierunek = 5;
					}
				}
				else if (aniUD == 0) {
					if (aniLR == 1) {
						sprite->spriteFlip = SDL_FLIP_NONE;
						sprite->Play("WalkL");
						//Game::kierunek = 1;
					}
					else if (aniLR == 2) {
						sprite->spriteFlip = SDL_FLIP_NONE;
						sprite->Play("Walk");
						//Game::kierunek = 0;
					}
					else if (aniLR == 0) {

					}
				}
				
		}


	}
	

};