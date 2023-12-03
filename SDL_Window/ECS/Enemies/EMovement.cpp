#include"EMovement.h"

int opt,aniLR,aniUD;

EMovement::EMovement() {}
EMovement::~EMovement() {}

int EMovement::WhereMove(int EPosX, int EPosY) {
	if (Game::ePosX3 > Game::pPosX + 10) {
		aniLR = 1;
	}
	else if (Game::ePosX3 < Game::pPosX - 10) {
		aniLR = 2;
	}
	else {
		aniLR = 0;
	}
	if (Game::ePosY3 > Game::pPosY + 10) {
		aniUD = 1;
	}
	else if (Game::ePosY3 < Game::pPosY - 10) {
		aniUD = 2;
	}
	else {
		aniUD = 0;
	}


	if (aniUD == 1) {
		if (aniLR == 0) { opt = 1; }
		else if (aniLR == 1) { opt = 2; }
		else if (aniLR == 2) {opt=3;}

	else if (aniUD == 2) {
			if (aniLR == 0) { opt = 4; }
			else if (aniLR == 1) { opt = 5; }
			else if (aniLR == 2) { opt = 6; }
	}
	else if (aniUD == 0) {
			if (aniLR == 1) { opt = 7; }
			else if (aniLR == 2) { opt = 8; }
			else if (aniLR == 0) { opt = 9; }
	}

	return opt;

}