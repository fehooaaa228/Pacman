#pragma once

#include <raylib.h>
#include "Player.h"
#include "Ghost.h"
#include "Dot.h"
#include "Powerup.h"
#include "GhostManager.h"
#include <vector>

class Application
{
public:
	Application();
	void run();
	void init();
	void renderFrame();
	void reset();
	void restart();
	void drawUI();
	void win();

private:
	Player p;
	std::vector<Dot> dots;
	std::vector<Powerup> powerups;
	GhostManager ghostManager;
	Texture2D background;
	int score = 0, highScore = 0;
	unsigned char level = 1;
};

