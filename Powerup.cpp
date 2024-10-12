#include "Powerup.h"
#include <raylib.h>
#include "Globals.h"

Powerup::Powerup(float x, float y) : Object(x, y) {}

void Powerup::draw() {
	DrawCircle(pos.x, pos.y, C_SIZE * 0.5, BEIGE);
}