#pragma once

#include "MovingObject.h"
#include "Globals.h"
#include "vec2.h"

class Ghost : public MovingObject {
public:
	float r = C_SIZE;
	int delay;
	bool free = false;
	bool alive = true;
	bool frightened = false;
	vec2 target;
	
	Ghost(float x = 0, float y = 0);

	bool collides(vec2 p);

	void update();
	void moveToTarget();
	void moveOut();
	void moveRandomly();
	void moveToGhostHouse();
	void move(float speed);
	void draw();
	void die();
	std::vector<vec2> findAvailableDirs();

private:
	int faze = 0;
};

