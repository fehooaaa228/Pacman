#include "GhostManager.h"
#include "Globals.h"

GhostManager::GhostManager() {
	ghosts[0] = Ghost(S_WIDTH / 2, SPACE_FOR_TEXT / 2 + C_SIZE * 12);
	ghosts[1] = Ghost(ghosts[0].pos.x, ghosts[0].pos.y + C_SIZE * 3);
	ghosts[2] = Ghost(ghosts[1].pos.x + C_SIZE * 2, ghosts[1].pos.y);
	ghosts[3] = Ghost(ghosts[1].pos.x - C_SIZE * 2, ghosts[1].pos.y);

	ghosts[0].free = true;
	ghosts[1].delay = FPS * 5;
	ghosts[2].delay = FPS * 10;
	ghosts[3].delay = FPS * 15;

	ghosts[0].target = vec2(C_SIZE * (map[0].size() - 4), 0);
	ghosts[1].target = vec2(C_SIZE * 4, 0);
	ghosts[2].target = vec2(0, C_SIZE * map.size());
	ghosts[3].target = vec2(C_SIZE * map[0].size(), C_SIZE * map.size());
}

Ghost* GhostManager::getGhosts() {
	return ghosts;
}

void GhostManager::update(vec2 playerPos) {
	if (mode != FRIGHTENED) {
		if (switchCd == 0) {
			switchMode(mode == SCATTERING ? CHASE : SCATTERING, playerPos);
		}
		else switchCd--;
	}
	else {
		if (frightenedMode == 0) {
			switchMode(lastMode, playerPos);
		}
		else frightenedMode--;
	}

	setTargets(playerPos);

	for (int i = 0; i < 4; i++) {
		ghosts[i].update();
	}
}

void GhostManager::switchMode(Modes m, vec2 playerPos) {
	if(mode == SCATTERING || mode == CHASE){
		for (int i = 0; i < 4; i++) {
			if (ghosts[i].free && ghosts[i].alive) ghosts[i].dir = ghosts[i].dir * -1;
		}
	}

	if (mode == FRIGHTENED) {
		for (int i = 0; i < 4; i++) {
			ghosts[i].frightened = false;
		}
	}

	switch (m) {
	case SCATTERING:
		setTargets(playerPos);

		switchCd = FPS * 7;

		break;
	case CHASE:
		setTargets(playerPos);

		switchCd = FPS * 20;

		break;
	case FRIGHTENED:
		for (int i = 0; i < 4; i++) {
			if(ghosts[i].alive)
				ghosts[i].frightened = true;
		}
		frightenedMode = frightenedModeDuration;
		lastMode = (mode == FRIGHTENED) ? lastMode : mode;
	}

	mode = m;
}

void GhostManager::setTargets(vec2 playerPos) {
	switch (mode) {
	case SCATTERING:
		if (ghosts[0].alive) ghosts[0].target = vec2(C_SIZE * (map[0].size() - 4), 0);
		if (ghosts[1].alive) ghosts[1].target = vec2(C_SIZE * 4, 0);
		if (ghosts[2].alive) ghosts[2].target = vec2(0, C_SIZE * map.size());
		if (ghosts[3].alive) ghosts[3].target = vec2(C_SIZE * map[0].size(), C_SIZE * map.size());

		break;
	case CHASE:
		for (int i = 0; i < 4; i++) {
			if (ghosts[i].free && ghosts[i].alive) ghosts[i].target = playerPos;
		}

		break;
	}
}