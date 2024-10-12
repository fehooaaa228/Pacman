#pragma once

#include "Globals.h"
#include "Dot.h"
#include "Powerup.h"
#include "Ghost.h"
#include "GhostManager.h"
#include "Player.h"
#include <vector>
#include <raylib.h>

class Application
{
public:
	Application();
	void run();
	void init();
	void renderFrame();
	void restartLevel();
	void restartGame();
	void drawUI();
	void win();
	void drawConsumables();
	void resetGhostsNPlayer();

private:
	Player p;
	std::vector<Dot> dots;
	std::vector<Powerup> powerups;
	GhostManager ghostManager;
	Texture2D background;
	int score = 0, highScore = 0;
	unsigned char level = 1;
};

