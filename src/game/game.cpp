#include <stdexcept>
#include <string>
#include <chrono>
#include "game.hpp"
#include "../common.h"

Game::Game() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		throw std::runtime_error("Failed to initialize SDL. SDL error: " + std::string(SDL_GetError()));
	}

	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);

	window = SDL_CreateWindow("SDL", (DM.w - WINDOW_WIDTH) / 2, (DM.h - WINDOW_HEIGHT) / 2, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		throw std::runtime_error("Failed to create window. Error: " + std::string(SDL_GetError()));
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		throw std::runtime_error("Failed to create renderer. Error: " + std::string(SDL_GetError()));
	}
}

void Game::start_game_loop() {
	float deltaTime;
	float frameTime = (float)1000 / MAX_FPS;

	while (running) {
		SDL_Event event;
		auto frameStartTime = std::chrono::high_resolution_clock().now();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				stop_game_loop();
			}

			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					stop_game_loop();
				}


			}

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			// update here

			SDL_RenderPresent(renderer);

			auto frameEndTime = std::chrono::high_resolution_clock().now();
			deltaTime = std::chrono::duration<float, std::chrono::milliseconds::period>(frameEndTime - frameStartTime).count();

			if (frameTime > deltaTime) {
				SDL_Delay(Uint32(frameTime - deltaTime));
			}
		}
	}
}

void Game::stop_game_loop() {
	running = false;
}
