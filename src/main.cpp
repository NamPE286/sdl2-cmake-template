#include <SDL2/SDL.h>
#include "game/game.hpp"

int SDL_main(int argc, char* argv[]) {
	Game game;
	
	game.start_game_loop();

	return 0;
}