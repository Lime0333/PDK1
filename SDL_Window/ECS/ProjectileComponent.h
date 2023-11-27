#pragma once

#include"ECS.h"
#include"Components.h"

class PrjectileComponent : public Component {
public:
	ProjectileComponent(int rng, int sp) : range(rng), speed(sp)
	{}
	~ProjectileComponent();

	void init() override{
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override {

		distance += speed;

		if (distance > range) {
			entity->destroy();
		}

		else if (transform->position.x > Game::camera.x + Game::camera.w || transform->position.y>Game::camera.y+Game::camera.h||transform->position.x<Game::camera.x||transform->position.y<Game::camera.y ) {
			entity->destroy();
		}
	}

private:
	TransformComponent* transform;

	int range=0, speed=0, distance=0;

};