#pragma once

#include "GameConfig.h"
#include "model/Model.h"
#include "view/View.h"
#include "controller/Controller.h"
#include "Unit.h"

class Game {
private:
	// Config
	const GameConfig config_;
	bool isGameRunning = false;

	// Model
	Model model_;
	View view_;
	Controller controller_;

	void loop();

public:
	Game(const GameConfig&);

	void start();
	void end();
	void win();
	void lose();
};