#include "GameManager.h"
#include <iostream>
#include "Game.h"

#undef main

int main(int argc, char* args[]) {

	doom_nukem::Game* game = new doom_nukem::Game();

	game->init(
		"Doom Nukem by Skunz",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		600 * 2, 400 * 2
	);
	game->start();

	delete game;

	return 0;
}
