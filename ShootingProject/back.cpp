#include "back.h"
#include "pch.h"

BACK::BACK()
{
	gh = LoadGraph("Picture/back1.png");
	x = y = MARGIN;

}

void BACK::Draw() {
	DrawGraph(x, y, gh, FALSE);
	DrawGraph(x, y - 460, gh, FALSE);
	if (y == 460 + MARGIN)
		y = 10;
}

void BACK::Move() {
	y += SCROLL_SPEED;
}

void BACK::All() {
	Draw();
	Move();
}