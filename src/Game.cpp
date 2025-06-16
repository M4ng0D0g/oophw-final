#include "Game.h"
#include <iostream>
#include <ctime>
#include <thread>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <chrono>
#include <cstddef>
#include <string>

Game::Game(const GameConfig& config)
: config_(config), model_(config_), view_(config_, model_), controller_(config_, model_) {}

void Game::start() {
	auto seed = static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count());
	std::srand(seed);
	model_.initialize();
	
	isGameRunning = true;
	loop();
}

void Game::end() {
	isGameRunning = false;
	// std::cout << "Final score: " << model_.getScore().toStr() << std::endl;
}

void Game::win() {
	std::cout << "You win!" << std::endl;
	end();
	std::string str;

	do {
		std::cout << "Continue? (Y/n): " << std::endl;
		std::cin >> str;
		for(auto& c : str) {
			if(c >= 'A' && c <= 'Z') c += 'a' - 'A';
		}
	}
	while(str != "y" && str != "n");

	if(str == "y") loop();
	else return;
}

void Game::lose() {
	std::cout << "You lose." << std::endl;
	end();
}

void Game::loop() {
	// initial setup
	std::cin.tie(0);
	std::ios::sync_with_stdio(0);
	configure_terminal();

	// init state
	clock_t startTime, endTime;

	// Main loop
	while(isGameRunning) {
		startTime = clock();

		// Game Flow
		if(!controller_.handleInput()) {
			end();
			break;
		}
		view_.resetLatest();
		controller_.operate();
		view_.updateGameObject();
		view_.render();

		if(false) {
			win();
			break;
		}
		else if(model_.isStucked()) {
			lose();
			break;
		}

		// view_.displayScore();

		endTime = clock();

		// frame rate normalization
		double time_taken = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
		if (time_taken > config_.SPF) continue;
		int frameDelay = int((config_.SPF - time_taken) * 1000); // 0.1 seconds
		if(frameDelay > 0) std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay)); // frame delay
	}
}