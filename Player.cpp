#include "Player.h"
#include "Globals.h"
#include <raylib.h>
#include <iostream>

Player::Player() : MovingObject(0, 0, 1, C_SIZE), targetDir(dir) {}
Player::Player(float x, float y) : MovingObject(x, y, PLAYER_SPEED, C_SIZE), targetDir(dir) {}

bool Player::collides(vec2 p) {
	return willCollide(p, '@');
}

void Player::update(std::vector<Dot>* dots, std::vector<Powerup>* powerups, Ghost* ghosts, int* score, GhostManager* ghostManager) {
	if (IsKeyPressed(KEY_UP)) targetDir = dirs[0];
	if (IsKeyPressed(KEY_RIGHT)) targetDir = dirs[1];
	if (IsKeyPressed(KEY_DOWN)) targetDir = dirs[2];
	if (IsKeyPressed(KEY_LEFT)) targetDir = dirs[3];

	correctPos();

	if (dir != targetDir) {
		if (!collides(pos + targetDir)) dir = targetDir;
	}

	if (!collides(pos + dir)) {
		pos += dir * speed;
	}
	
	for (int i = 0; i < dots->size(); i++) {
		vec2 diff = (*dots)[i].pos - pos;
		if (diff.x * diff.x + diff.y * diff.y <= r * r * 0.8) {
			(*dots).erase((*dots).begin() + i);
			*score += 10;
			break;
		}
	}
	
	for (int i = 0; i < 4; i++) {
		vec2 nPos = ghosts[i].pos - pos;
	
		if (nPos.x * nPos.x + nPos.y * nPos.y <= r * r) {
			if (ghosts[i].frightened && ghosts[i].alive) {
				ghosts[i].die();
				*score += killGain;
				killGain *= 2;
				if (killGain == 1600) killGain = 200;
			}
			else if(!ghosts[i].frightened && ghosts[i].alive){
				alive = false;
			}
		}
	}

	for (int i = 0; i < powerups->size(); i++) {
		vec2 diff = (*powerups)[i].pos - pos;
		if (diff.x * diff.x + diff.y * diff.y <= r * r * 0.8) {
			(*powerups).erase((*powerups).begin() + i);
			ghostManager->switchMode(FRIGHTENED, pos);

			break;
		}
	}
	
	if (pos.x <= 0 || pos.x > S_WIDTH) pos.x = abs(pos.x - S_WIDTH);
	if (pos.y <= 0 || pos.y > S_HEIGHT) pos.y = abs(pos.y - S_HEIGHT);
}

void Player::draw() {
	DrawCircle(pos.x, pos.y, r * 0.8, YELLOW);
}