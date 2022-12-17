#include <span>

#include "pch.h"
#include "player.h"
#include "control.h"


PLAYER::PLAYER()
{

	if (-1 == LoadDivGraph("Picture/charall.png", 12, 3, 4, 49, 66, gh)) {
		MSG("error");
	}


	width = 49;
	height = 66;


	move = 1.0f;

	xcount = 0, ycount = 0;
	ix = 0, iy = 0, result = 0;

	x = 180;
	y = 400;

	life = true;

	memset(shot, 0, sizeof(shot));

	int temp = LoadGraph("Picture/shot.png");
	int w, h;
	GetGraphSize(temp, &w, &h);

	for (int i = 0; i < PSHOT_NUM; ++i) {
		shot[i].flag = false;
		shot[i].gh = temp;
		shot[i].width = w;
		shot[i].height = h;
	}

	count = 0;


}
void PLAYER::Move()
{

	if (key[KEY_INPUT_LEFT] == 1 || key[KEY_INPUT_RIGHT] == 1) {

		if (key[KEY_INPUT_UP] == 1 || key[KEY_INPUT_DOWN] == 1) {
			move = 0.71f;
		}
		else {
			move = 1.0f;
		}
	}
	else if (key[KEY_INPUT_UP] == 1 || key[KEY_INPUT_DOWN] == 1) {
		move = 1.0f;
	}


	if (key[KEY_INPUT_LEFT] == 1) {
		x -= (int)PLAYER_SPEED * move;
	}
	if (key[KEY_INPUT_RIGHT] == 1) {
		x += (int)PLAYER_SPEED * move;

	}
	if (key[KEY_INPUT_UP] == 1) {
		y -= (int)PLAYER_SPEED * move;

	}
	if (key[KEY_INPUT_DOWN] == 1) {
		y += (int)PLAYER_SPEED * move;

	}

	//<span class = "stress" >
	if (x > 400 - MARGIN) {
		x = 400 - MARGIN;
	}
	else if (x < MARGIN) {
		x = MARGIN;
	}

	if (y > 480 - height / 2 - MARGIN) {
		y = 480 - height / 2 - MARGIN;
	}
	else if (y < height / 2 + MARGIN) {
		y = height / 2 + MARGIN;
	}
	//< / span>


	if (key[KEY_INPUT_LEFT] == 1) {
		if (xcount > 0)
			xcount = 0;
		--xcount;

	}
	if (key[KEY_INPUT_RIGHT] == 1) {
		if (xcount < 0)
			xcount = 0;
		++xcount;
	}
	if (key[KEY_INPUT_UP] == 1) {
		if (ycount > 0)
			ycount = 0;
		--ycount;
	}
	if (key[KEY_INPUT_DOWN] == 1) {
		if (ycount < 0)
			ycount = 0;
		++ycount;
	}


	ix = abs(xcount) % 30 / 10;
	iy = abs(ycount) % 30 / 10;

	if (xcount > 0) {
		ix += 3;
		result = ix;
	}
	else if (xcount < 0) {
		ix += 9;
		result = ix;
	}

	if (ycount > 0) {
		iy += 6;
		result = iy;
	}
	else if (ycount < 0) {
		iy += 0;
		result = iy;
	}

	if (move == 0.71f)
		result = ix;


	if (key[KEY_INPUT_LEFT] != 1 && key[KEY_INPUT_RIGHT] != 1) {
		xcount = 0;
	}
	if (key[KEY_INPUT_UP] != 1 && key[KEY_INPUT_DOWN] != 1) {
		ycount = 0;
	}

}

void PLAYER::Draw()
{
	for (int i = 0; i < PSHOT_NUM; ++i) {
		if (shot[i].flag) {
			DrawGraph(shot[i].x - shot[i].width / 2, shot[i].y - shot[i].height / 2, shot[i].gh, TRUE);
		}
	}

	if (life) {
		DrawGraph(x - width / 2, y - height / 2, gh[result], TRUE);
	}
}

void PLAYER::Shot() {

	s_shot = false;

	if (key[KEY_INPUT_SPACE] == 1 && count % 6 == 0) {
		for (int i = 0; i < PSHOT_NUM; ++i) {
			if (shot[i].flag == false) {
				shot[i].flag = true;
				shot[i].x = x;
				shot[i].y = y;
				break;
			}
		}
		//ショットサウンドフラグを立てる
		s_shot = true;

	}

	for (int i = 0; i < PSHOT_NUM; ++i) {
		if (shot[i].flag) {
			shot[i].y -= PSHOT_SPEED;

			if (shot[i].y < -10) {
				shot[i].flag = false;
			}
		}
	}


}

void PLAYER::GetPosition(double* x, double* y)
{
	*x = this->x;
	*y = this->y;

}

bool PLAYER::GetShotSound()
{
	return s_shot;
}

bool PLAYER::GetShotPosition(int index, double* x, double* y)
{
	if (shot[index].flag) {
		*x = shot[index].x;
		*y = shot[index].y;
		return true;
	}
	else {
		return false;
	}

}

void PLAYER::SetShotFlag(int index, bool flag)
{
		shot[index].flag = flag;
}



void PLAYER::All()
{
	Move();
	Shot();
	Draw();

	++count;
}