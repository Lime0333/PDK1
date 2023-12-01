#pragma once

#include"Components.h"
#include"SDL.h"
#include"../TextureManager.h"
#include"Animation.h"
#include<map>
#include"../AssetManager.h"

class SpriteComponent : public Component {
private:

	TransformComponent*transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0, speed = 100;

public:

	int animIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(std::string id) {
		setTex(id);
	}

	SpriteComponent(std::string id, bool isAnimated) {
		animated = isAnimated;

		Animation idle = Animation(0, 1, 100);
		Animation walk = Animation(1, 2, 250);

		Animation idleUP = Animation(2, 1, 100);
		Animation walkUP = Animation(3, 2, 250);

		Animation idleDOWN = Animation(4, 1, 100);
		Animation walkDOWN = Animation(5, 2, 250);

		Animation idleL = Animation(6, 1, 100);
		Animation walkL = Animation(7, 2, 250);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		animations.emplace("IdleUP", idleUP);
		animations.emplace("WalkUP", walkUP);

		animations.emplace("IdleDOWN", idleDOWN);
		animations.emplace("WalkDOWN", walkDOWN);

		animations.emplace("IdleL", idleL);
		animations.emplace("WalkL", walkL);


		Play("Idle");

		setTex(id);
	}

	~SpriteComponent() {
	}

	void setTex(std::string id) {
		texture = Game::assets->GetTexture(id);
	}

	void init() override {

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override {

		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x-Game::camera.x);
		destRect.y = static_cast<int>(transform->position.y-Game::camera.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;

	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void Play(const char* animName) {
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}

};