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
		


		Animation idle2 = Animation(8, 1, 100);
		Animation walk2 = Animation(9, 2, 250);

		Animation idleUP2 = Animation(10, 1, 100);
		Animation walkUP2 = Animation(11, 2, 250);

		Animation idleDOWN2 = Animation(12, 1, 100);
		Animation walkDOWN2 = Animation(13, 2, 250);

		Animation idleL2 = Animation(14, 1, 100);
		Animation walkL2 = Animation(15, 2, 250);


		Animation Menu0 = Animation(0, 5, 1);
		Animation Menu1 = Animation(1, 1, 200);
		Animation Menu2 = Animation(2, 1, 200);
		Animation Menu3 = Animation(3, 1, 200);
		Animation Menu4 = Animation(4, 1, 200);
		Animation Menu5 = Animation(5, 1, 200);
		Animation Menu6 = Animation(6, 1, 200);
		Animation MenuBlank = Animation(7, 1, 200);
		Animation Skin0 = Animation(8, 2, 500);
		Animation Skin1 = Animation(9, 2, 500);
		Animation Skin2 = Animation(10, 2, 500);
		Animation Skin3 = Animation(11, 2, 500);
		Animation Skin4 = Animation(12, 2, 500);
		Animation Skin5 = Animation(13, 2, 500);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		animations.emplace("IdleUP", idleUP);
		animations.emplace("WalkUP", walkUP);

		animations.emplace("IdleDOWN", idleDOWN);
		animations.emplace("WalkDOWN", walkDOWN);

		animations.emplace("IdleL", idleL);
		animations.emplace("WalkL", walkL);


		animations.emplace("Menu0", Menu0);
		animations.emplace("Menu1", Menu1);
		animations.emplace("Menu2", Menu2);
		animations.emplace("Menu3", Menu3);
		animations.emplace("Menu4", Menu4);
		animations.emplace("Menu5", Menu5);
		animations.emplace("Menu6", Menu6);
		animations.emplace("MenuBlank", MenuBlank);
		animations.emplace("Skin0", Skin0);
		animations.emplace("Skin1", Skin1);
		animations.emplace("Skin2", Skin2);
		animations.emplace("Skin3", Skin3);
		animations.emplace("Skin4", Skin4);
		animations.emplace("Skin5", Skin5);


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