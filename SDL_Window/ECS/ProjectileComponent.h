#pragma once

#include"ECS.h"
#include"Components.h"
#include"../Vector2D.h"

class ProjectileComponent : public Component {
public:
	//ProjectileComponent() : range(0), speed(0){}
	ProjectileComponent(int rng, int sp, Vector2D vel) : range(rng), speed(sp), velocity(vel)
	{}

	~ProjectileComponent() 
	{}

	void init() override{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
	}

	void update() override {

		distance += speed;

		if (distance > range) {
			std::cout << "Out of range" << std::endl;
			entity->destroy();
		}

		else if (transform->position.x > Game::camera.x + Game::camera.w || transform->position.y>Game::camera.y+Game::camera.h||transform->position.x<Game::camera.x||transform->position.y<Game::camera.y ) {
			std::cout << "Out of bounds" << std::endl;
			entity->destroy();
		}
	}

private:
	TransformComponent* transform;

	int range=0, speed=0, distance=0;
	Vector2D velocity;

};