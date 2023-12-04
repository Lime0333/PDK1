#pragma once

#include"Emovement.h"

class E1 :public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	int aniUD = 0, aniLR = 0,kierunek=0;
	bool alive=true;
	int Eid = 1;

	const static int socialDistance = 200;

	int PozX, PozY , cool;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {

		PozX = Game::ePosX1;
		PozY = Game::ePosY1;

		cool = Game::eCool1;

		if (Game::eHP1 <= 0 and alive) {
			for (float i = 30; i > 0; i=i-10) {
				transform->velocity.y = i;
			}
			
			
			alive = false;
		}

		if (alive) {

			if (cool < 0) {
				Game::ESpawnP(Eid, kierunek);
			}
			//transform->velocity.y = -1;

			//std::cout << Game::ePosX <<"   " << Game::ePosY << std::endl;

			//0=right 1=left 2=up 3=down 4=right-up 5=right-down 6=left-up 7=left-down

			if (PozX > Game::pPosX + 10 + socialDistance) {
				transform->velocity.x = -0.5;
				aniLR = 1;
			}
			else if (PozX < Game::pPosX - 10 - socialDistance) {
				transform->velocity.x = 0.5;
				aniLR = 2;
			}
			else {

				transform->velocity.x = 0;
				aniLR = 0;
				sprite->Play("Idle");
			}
			if (PozY > Game::pPosY + 10 + socialDistance) {
				transform->velocity.y = -0.5;
				aniUD = 1;
			}
			else if (PozY < Game::pPosY - 10 - socialDistance) {
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
					kierunek = 2;
				}
				else if (aniLR == 1) {
					//UL anim
					kierunek = 6;
				}
				else if (aniLR == 2) {
					//UR anim
					kierunek = 4;
				}
			}
			else if (aniUD == 2) {
				if (aniLR == 0) {
					sprite->spriteFlip = SDL_FLIP_NONE;
					sprite->Play("WalkDOWN");
					kierunek = 3;
				}
				else if (aniLR == 1) {
					//DL anim
					kierunek = 7;
				}
				else if (aniLR == 2) {
					//DR anim
					kierunek = 5;
				}
			}
			else if (aniUD == 0) {
				if (aniLR == 1) {
					sprite->spriteFlip = SDL_FLIP_NONE;
					sprite->Play("WalkL");
					kierunek = 1;
				}
				else if (aniLR == 2) {
					sprite->spriteFlip = SDL_FLIP_NONE;
					sprite->Play("Walk");
					kierunek = 0;
				}
				else if (aniLR == 0) {

				}
			}

		}


	}
	

};