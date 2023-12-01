#pragma once

#include"../Game.hpp"
#include"ECS.h"
#include"Components.h"
#include"../AssetManager.h"


class KeyboardController :public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	
	

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
				break;

			case SDLK_a:
				transform->velocity.x = -1;
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				Game::directionChange(1);
				break;

			case SDLK_d:
				transform->velocity.x = 1;
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_NONE;
				Game::directionChange(0);
				break;

			case SDLK_s:
				transform->velocity.y = 1;
				sprite->Play("WalkDOWN");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				Game::directionChange(3);
				break;

			case SDLK_LSHIFT:
				Game::spawnProjectile();

			default:

				break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				transform->velocity.y = 0;
				sprite->Play("IdleUP");
				break;

			case SDLK_a:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				
				break;

			case SDLK_d:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				break;

			case SDLK_s:
				transform->velocity.y = 0;
				sprite->Play("IdleDOWN");
				break;

			case SDLK_ESCAPE:
				Game::isRunning = false;
			default:

				break;
			}
		}
	}
};