#include "Ghost.h"
#include <raylib.h>

Ghost::Ghost(float x, float y, int delay, Color color) : MovingObject(x, y, GHOST_SPEED, C_SIZE), delay(delay), color(color) {}

bool Ghost::collides(vec2 p) {
	return willCollide(p, '@') || willCollide(p, 'x');
}

void Ghost::draw() {
	if (alive) {
		DrawCircle(pos.x, pos.y, r, (frightened) ? BLUE : color);
	}
	else {
		DrawCircle(pos.x, pos.y, r * 0.3, WHITE);
	}
}

void Ghost::update() {
	if (delay < 1) {
		if (alive) {
			if (!free) {
				moveOut();
			}
			else {
				if (!frightened) moveToTarget();
				else moveRandomly();
			}
		}
		else {
			moveToGhostHouse();
		}
	}
	else {
		moveUpNDown();
		delay--;
	}

	draw();
}

void Ghost::moveUpNDown() {
	if (pos.y < C_SIZE * 16 + 10) {
		dir = dirs[2];
	}
	else if (pos.y > C_SIZE * 17 + 10) {
		dir = dirs[0];
	}

	pos += dir;
}

std::vector<vec2> Ghost::findAvailableDirs() {
	correctPos();

	bool restricted = pos == vec2(C_SIZE * 13, C_SIZE * 14) || pos == vec2(C_SIZE * 16, C_SIZE * 14) || pos == vec2(C_SIZE * 13, C_SIZE * 26) || pos == vec2(C_SIZE * 16, C_SIZE * 26);

	std::vector<vec2> ad;

	for (int i = 0; i < 4; i++) {
		if (dirs[i] != -dir && !collides(pos + dirs[i])) {
			if(!(restricted && dirs[i] == dirs[0])) ad.push_back(dirs[i]);
		}
	}

	return ad;
}

void Ghost::moveRandomly() {
	std::vector<vec2> ad = findAvailableDirs();
	if (ad.size() != 0) {
		dir = ad[rand() % ad.size()];

		move(speed * 0.7);
	}
}

void Ghost::moveOut() {
	if (pos.x != S_WIDTH / 2) {
		pos += vec2(sign(S_WIDTH / 2 - pos.x), 0);
	}
	else {
		pos += vec2(0, -1);

		if (pos == vec2(S_WIDTH / 2, SPACE_FOR_TEXT / 2 + C_SIZE * 12)) {
			free = true;
			dir = dirs[1];
		}
	}
}

void Ghost::moveToTarget() {
	std::vector<vec2> ad = findAvailableDirs();

	vec2 nd;
	float mind = 10000;

	for (int i = 0; i < ad.size(); i++) {
		float l = length(target - (pos + ad[i]));
		if (l < mind) {
			mind = l;
			nd = ad[i];
		}
	}

	dir = nd;
	move(speed);
}

void Ghost::moveToGhostHouse() {
	switch (faze) {
	case 0:
		moveToTarget();

		if (length(target - pos) < 5) {
			pos.x = S_WIDTH / 2;
			faze++;
		}

		break;
	case 1:
		pos += dirs[2] * speed;

		if (pos.y > C_SIZE * 16) faze++;

		break;

	case 2:
		pos += dirs[0];

		if (length(target - pos) < 5) {
			pos = target;
			alive = true;
			speed /= 2;
			faze = 0;
		}

		break;
	}

}

void Ghost::move(float _speed) {
	pos += dir * _speed;
}

void Ghost::die() {
	target = vec2(S_WIDTH / 2, C_SIZE * 14);
	alive = false;
	if (!free) {
		free = true;
		faze = 1;
	}
	speed *= 2;
	frightened = false;
}
