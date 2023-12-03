#include"AssetManager.h"
#include"ECS/Components.h"

int kierunek = 0;

AssetManager::AssetManager(Manager* man) : manager(man){

}

AssetManager::~AssetManager() {

}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id, bool LR,int owner)
{
	auto& projectile(manager->addEntity());

	if (LR) {
		projectile.addComponent<TransformComponent>(pos.x, pos.y, 8, 20, 1);
	}
	else {
		projectile.addComponent<TransformComponent>(pos.x, pos.y, 20, 8, 1);
	}
	projectile.addComponent<SpriteComponent>(id, false);
	projectile.addComponent<ProjectileComponent>(range, speed, vel);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::AddTexture(std::string id, const char* path) {
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id) {
	return textures[id];
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize) {
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}
TTF_Font* AssetManager::GetFont(std::string id) {
	return fonts[id];
}