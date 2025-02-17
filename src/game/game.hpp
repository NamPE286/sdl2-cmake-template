#pragma once

#include <SDL2/SDL.h>

class Game {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool running = true;

public:
	Game();
	void start_game_loop();
	void stop_game_loop();
};