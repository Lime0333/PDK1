#pragma once
#include"../Components.h"


class EMovement : public Component {
public:

	EMovement();
	~EMovement();

	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	int WhereMove(int EPosX, int EPosY);
};