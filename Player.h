#pragma once

#include "MovingObject.h"
#include "Dot.h"
#include "Ghost.h"
#include <vector>
#include "GhostManager.h"
#include "Powerup.h"

class Player : public MovingObject
{
public:
	vec2 targetDir;
	int r = C_SIZE;
	bool alive = true;
	int lives = 4;
	int killGain = 200;

	Player(float x = 0, float y = 0);

	bool collides(vec2 p);
	void update(std::vector<Dot>* dots, std::vector<Powerup>* powerups, int* score, GhostManager* ghostManager);
	void draw();
};