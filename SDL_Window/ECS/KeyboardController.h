#pragma once

#include"../Game.hpp"
#include"ECS.h"
#include"Components.h"
#include"../AssetManager.h"


class KeyboardController :public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	
	bool walking=false;
	

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				transform->velocity.y = -1;
				sprite->Play("WalkUP");
				sprite->spriteFlip = SDL_FLIP_NONE;
				Game::directionChange(2);
				walking = true;
				break;

			case SDLK_a:
				transform->velocity.x = -1;
				sprite->Play("WalkL");
				sprite->spriteFlip = SDL_FLIP_NONE;
				Game::directionChange(1);
				walking = true;
				break;

			case SDLK_d:
				transform->velocity.x = 1;
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_NONE;
				Game::directionChange(0);
				walking = true;
				break;

			case SDLK_s:
				transform->velocity.y = 1;
				sprite->Play("WalkDOWN");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				Game::directionChange(3);
				walking = true;
				break;

			case SDLK_LSHIFT:
				if (walking == false) {
					Game::spawnProjectile();
				}
			default:

				break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				transform->velocity.y = 0;
				sprite->Play("IdleUP");
				walking = false;
				break;

			case SDLK_a:
				transform->velocity.x = 0;
				sprite->Play("IdleL");
				walking = false;
				break;

			case SDLK_d:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				walking = false;
				break;

			case SDLK_s:
				transform->velocity.y = 0;
				sprite->Play("IdleDOWN");
				walking = false;
				break;

			case SDLK_ESCAPE:
				Game::isRunning = false;
			default:

				break;
			}
		}
	}
};