#pragma once


#include"../../Game.hpp"
#include"../ECS.h"
#include"../Components.h"
#include"../../AssetManager.h"

class Menu :public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	float CPosX, CPosY;
	bool menuOpening = false;
	int menuCool = 0;

	int MChoose = 1;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {

		CPosX = Game::camera.x;
		CPosY = Game::camera.y;

		sprite->Play("MenuBlank");

		//transform->velocity.y = 0;
		//transform->velocity.x = 0;

		if (Game::FlashPosX < CPosX+1 and Game::FlashPosX < CPosX - 5) {
			transform->velocity.x = 1;
		}
		else if (Game::FlashPosX > CPosX + 1 and Game::FlashPosX > CPosX -5) {
			transform->velocity.x = -1;
		}
		else {
			transform->velocity.x = 0;
		}

		if (Game::FlashPosY < CPosY + 1 and Game::FlashPosY < CPosY - 5) {
			transform->velocity.y = 1;
		}
		else if (Game::FlashPosY > CPosY + 1 and Game::FlashPosY > CPosY - 5) {
			transform->velocity.y = -1;
		}
		else {
			transform->velocity.y = 0;
		}

		if (menuCool > 0 and Game::unpaused==false) {
			menuCool--;
		}

		

		if (menuOpening) {
			sprite->Play("Menu1");
			if (menuCool <= 0) {
				menuOpening = false;
			}
		}
		else if(Game::unpaused==false){
			switch (MChoose)
			{
			case 1:
				sprite->Play("Menu2");
				break;
			case 2:
				sprite->Play("Menu3");
				break;
			case 3:
				sprite->Play("Menu4");
				break;
			case 4:
				sprite->Play("Menu5");
				break;
			case 5:
				sprite->Play("Menu6");
				break;

			default:
				break;
			}
		}
		else {
			sprite->Play("MenuBlank");
		}

		if (Game::unpaused == false and menuOpening == false) {
			if (Game::event.type == SDL_KEYUP) {
				switch (Game::event.key.keysym.sym) {
				case SDLK_e:
				case SDLK_SPACE:
				case SDLK_RETURN:
					system("BAT\\menuCLICK.bat");
					switch (MChoose) {
					case 1:
						menuCool = 50;
						Game::unpaused = true;
						system("BAT\\wait1.bat");
						system("BAT\\menuONOFF.bat");
						
						break;
					case 2:
						//change skin
						break;
					case 3:
						Game::isRunning = false;
						break;
					case 4:
						system("BAT\\VLC64installer.bat");
						break;
					case 5:
						system("BAT\\raport.bat");
						break;
					default:
						break;
					}
					break;
				case SDLK_p:
					menuCool = 50;
					Game::unpaused = true;
					system("BAT\\wait1.bat");
					system("BAT\\menuONOFF.bat");
					
					break;
				case SDLK_UP:
					system("BAT\\menuSwitch.bat");
					system("BAT\\wait02.bat");
					MChoose--;
					break;
				case SDLK_w:
					system("BAT\\menuSwitch.bat");
					system("BAT\\wait02.bat");
					MChoose--;
					break;
				case SDLK_DOWN:
					system("BAT\\menuSwitch.bat");
					system("BAT\\wait02.bat");
					MChoose++;
					break;
				case SDLK_s:
					system("BAT\\menuSwitch.bat");
					system("BAT\\wait02.bat");
					MChoose++;
					break;
				default:

					break;
				}

				if (MChoose < 1) {
					MChoose = 5;
				}
				else if (MChoose > 5) {
					MChoose = 1;
				}


			}
		}

		else if (Game::event.type == SDL_KEYUP and Game::unpaused==true) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_p:
				
				Game::unpaused = false;
				system("BAT\\menuONOFF.bat");
				sprite->Play("Menu0");
				
				menuCool = 50;
				menuOpening = true;
				break;

			default:

				break;
			}

		}

		
		

	}
};
