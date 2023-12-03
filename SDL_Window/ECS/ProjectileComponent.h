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

		else{
			if (transform->position.x < Game::ePosX1 + 110 and
				transform->position.x > Game::ePosX1 and
				transform->position.y < Game::ePosY1 + 110 and
				transform->position.y > Game::ePosY1
				) {
				entity->destroy();
				Game::eHP1 = Game::eHP1 - 20;
				std::cout << "Enemy 1 hit! HP: " << Game::eHP1 << std::endl;
			}

			if (transform->position.x < Game::ePosX2 + 110 and
				transform->position.x > Game::ePosX2 and
				transform->position.y < Game::ePosY2 + 110 and
				transform->position.y > Game::ePosY2
				) {
				entity->destroy();
				Game::eHP2 = Game::eHP2 - 20;
				std::cout << "Enemy 2 hit! HP: " << Game::eHP2 << std::endl;
			}

			if (transform->position.x < Game::ePosX3 + 1100 and
				transform->position.x > Game::ePosX3 and
				transform->position.y < Game::ePosY3 + 110 and
				transform->position.y > Game::ePosY3
				) {
				entity->destroy();
				Game::eHP3 = Game::eHP3 - 20;
				std::cout << "Enemy 3 hit! HP: " << Game::eHP3 << std::endl;
			}

		}
	}

private:
	TransformComponent* transform;

	int range=0, speed=0, distance=0;
	Vector2D velocity;

};