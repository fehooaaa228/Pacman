#include "Application.h"
#include <iostream>

Application::Application() {}

void Application::run() {
	InitWindow(S_WIDTH, S_HEIGHT, "Pacman");
	SetTargetFPS(FPS);
	init();

	Image back = LoadImage("imgs/background.png");
	ImageResize(&back, S_WIDTH, S_HEIGHT - SPACE_FOR_TEXT);
	background = LoadTextureFromImage(back);

	while (!WindowShouldClose()) {
		renderFrame();
	}
}

void Application::resetGhostsNPlayer() {
	p.pos = vec2(S_WIDTH / 2, C_SIZE * 26);

	ghostManager = GhostManager(level);
}

void Application::init() {
	dots.clear();
	powerups.clear();

	resetGhostsNPlayer();

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] == '.') dots.push_back(Dot(j * C_SIZE + C_SIZE, i * C_SIZE + C_SIZE));
			if (map[i][j] == 'b') powerups.push_back(Powerup(j * C_SIZE + C_SIZE, i * C_SIZE + C_SIZE));
		}
	}
}

void Application::drawConsumables() {
	for (int i = 0; i < powerups.size(); i++) {
		powerups[i].draw();
	}

	for (int i = 0; i < dots.size(); i++) {
		dots[i].draw();
	}
}

void Application::restartLevel() {
	p.alive = true;
	resetGhostsNPlayer();
}

void Application::win() {
	level++;
	init();
}

void Application::restartGame() {
	p.alive = true;
	p.lives = 4;
	score = 0;
	level = 0;
	init();
}

void Application::drawUI() {
	DrawTexture(background, 0, SPACE_FOR_TEXT / 2, WHITE);
	DrawText("HIGH SCORE", S_WIDTH / 2 - 90, 0, 30, WHITE);
	DrawText(TextFormat("%02i", score), 100, C_SIZE, 30, WHITE);
	DrawText(TextFormat("%02i", highScore), S_WIDTH / 2 - 50, C_SIZE, 30, WHITE);
	for (int i = 0; i < p.lives; i++) {
		DrawCircle(50 * i + 50, C_SIZE * 35 - 10, C_SIZE * 0.7, YELLOW);
	}
}

void Application::renderFrame() {
	BeginDrawing();

	ClearBackground(BLACK);
	drawUI();
	drawConsumables();

	ghostManager.update(p.pos, p.dir, dots.size());

	p.update(&dots, &powerups, &score, &ghostManager);

	if (score > highScore) highScore = score;
	if (dots.size() == 0) {
		win();
	}

	if (!p.alive) {
		p.lives--;
		if (p.lives == 0) {
			restartGame();
		}
		else restartLevel();
	}

	p.draw();

	EndDrawing();
}