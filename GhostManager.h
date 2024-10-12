#pragma once

#include "Ghost.h"
#include "vec2.h"
#include <vector>

class GhostManager
{
public:
	Modes mode = SCATTERING;
	int frightenedModeDuration = FPS * 9, frightenedMode = frightenedModeDuration;

	GhostManager();

	void update(vec2 playerPos);
	void switchMode(Modes m, vec2 playerPos);
	void setTargets(vec2 playerPos);
	Ghost* getGhosts();

private:
	Ghost* ghosts = new Ghost[4];
	int switchCd = FPS * 7;
	Modes lastMode;
};

