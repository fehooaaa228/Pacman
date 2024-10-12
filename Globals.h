#pragma once

#include <vector>
#include <string>
#include "vec2.h"

const std::vector<std::string> map{
	"                             ",
	"                             ",
	"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
	"@............ @............ @",
	"@.    .     . @.     .    . @",
	"@b @@@. @@@@. @. @@@@. @@@b @",
	"@. @@@. @@@@. @. @@@@. @@@. @",
	"@.......................... @",
	"@.    .  .        .  .    . @",
	"@. @@@. @. @@@@@@@. @. @@@. @",
	"@...... @.... @.... @...... @",
	"@     . @     @     @.      @",
	"@@@@@@. @@@@  @  @@@@. @@@@@@",
	"     @. @           @. @     ",
	"     @. @           @. @     ",
	"@@@@@@. @  @@@@@@@  @. @@@@@@ ",
	"     x.    @     @   . x      ",
	"     x.    @     @   . x      ",
	"@@@@@@. @  @@@@@@@  @. @@@@@@ ",
	"     @. @           @. @     ",
	"     @. @           @. @     ",
	"@@@@@@. @  @@@@@@@  @. @@@@@@",
	"@............ @............ @",
	"@.    .     . @.     .    . @",
	"@. @@@. @@@@. @. @@@@. @@@. @",
	"@b.. @................ @..b @",
	"@  . @.  .        .  . @.   @",
	"@@@. @. @. @@@@@@@. @. @. @@@",
	"@...... @.... @.... @...... @",
	"@.      @   . @.    @     . @",
	"@. @@@@@@@@@. @. @@@@@@@@@. @",
	"@.......................... @",
	"@                           @",
	"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
	"                             ",
	"                             ",
};

const unsigned short FPS = 240;

const unsigned short C_SIZE = 28;

const unsigned short SPACE_FOR_TEXT = C_SIZE * 4;

const unsigned short S_WIDTH = C_SIZE * map[0].size();
const unsigned short S_HEIGHT = C_SIZE * map.size();

const float GHOST_SPEED = 1;
const float PLAYER_SPEED = 1.5;

static std::vector<vec2> dirs{ vec2(0, -1), vec2(-1, 0), vec2(0, 1), vec2(1, 0) };

enum Modes {
	SCATTERING,
	CHASE,
	FRIGHTENED
};