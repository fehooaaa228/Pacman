#include "Application.h"
#include "Globals.h"
#include <raylib.h>

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

void Application::init() {
	dots.clear();
	powerups.clear();

	ghostManager = GhostManager();

	p = Player(S_WIDTH / 2, C_SIZE * 26);

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] == '.') dots.push_back(Dot(j * C_SIZE + C_SIZE, i * C_SIZE + C_SIZE));
			if (map[i][j] == 'b') powerups.push_back(Powerup(j * C_SIZE + C_SIZE, i * C_SIZE + C_SIZE));
		}
	}
}

void Application::reset() {
	p.alive = true;
	ghostManager = GhostManager();
	p.pos = vec2(S_WIDTH / 2, C_SIZE * 26);
}

void Application::win() {
	level++;
	init();
}

void Application::restart() {
	p.alive = true;
	score = 0;
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

	for (int i = 0; i < powerups.size(); i++) {
		powerups[i].draw();
	}

	for (int i = 0; i < dots.size(); i++) {
		dots[i].draw();
	}

	ghostManager.update(p.pos);

	p.update(&dots, &powerups, ghostManager.getGhosts(), &score, &ghostManager);
	if (score > highScore) highScore = score;
	if (dots.size() == 0) {
		win();
	}

	p.draw();

	if (!p.alive) {
		p.lives--;
		if (p.lives == 0) {
			restart();
		}
		else reset();
	}

	EndDrawing();
}