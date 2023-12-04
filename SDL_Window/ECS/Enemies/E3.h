#pragma once

#include"Emovement.h"

class E3 :public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	int aniUD = 0, aniLR = 0,kierunek=0;
	bool alive = true;
	int PozX, PozY,cool;
	int Eid = 3, socialDistance = 250;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {

		PozX = Game::ePosX3;
		PozY = Game::ePosY3;

		cool = Game::eCool3;

		if (Game::eHP3 <= 0 and alive) {
			for (float i = 30; i > 0; i = i - 10) {
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
					//0=right 1=left 2=up 3=down 4=right-up 5=right-down 6=left-up 7=left-down
					switch (kierunek) {
					case 0:
						sprite->Play("Idle");
						break;
					case 1:
						sprite->Play("IdleL");
						break;
					case 2:
						sprite->Play("IdleUP");
						break;
					case 3:
						sprite->Play("IdleDOWN");
						break;
					case 4:
						sprite->Play("Idle");
						break;
					case 5:
						sprite->Play("Idle");
						break;
					case 6:
						sprite->Play("IdleL");
						break;
					case 7:
						sprite->Play("IdleL");
						break;
					default:
						break;
					}
				}
			}

		}


	}


};