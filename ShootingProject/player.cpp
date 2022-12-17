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

	x = PLAYER_INITX;
	y = PLAYER_INITY;

	life = PLAYER_LIFE;
	damageflag = false;
	endflag = false;
	dcount = 0;

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
	s_shot = false;


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

	//生きてれば描画
	if (damageflag) {
		if (dcount > 20) {
			if (dcount % 2 == 0) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 140);
				DrawGraph(PLAYER_INITX - width / 2, PLAYER_INITY - height / 2 + 60 - (dcount - 20), gh[1], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else {
				DrawGraph(PLAYER_INITX - width / 2, PLAYER_INITY - height / 2 + 60 - (dcount - 20), gh[1], TRUE);
			}
		}
		++dcount;
		if (dcount == 80) {
			damageflag = false;
			dcount = 0;
			//座標を初期値に戻す
			x = PLAYER_INITX;
			y = PLAYER_INITY;
			//上向きの画像にする
			result = 1;
		}
	}
	else {
		//通常描画
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

void PLAYER::SetDamageFlag()
{
	damageflag = true;
	--life;
	//消滅エフェクトのフラグを立てる
	effect_pdead.SetFlag(x, y);

}

bool PLAYER::GetDamageFlag()
{
	return damageflag;
}

int PLAYER::GetLife()
{
	return life;
}




void PLAYER::All()
{
	//消滅してないときだけ実行
	if (!damageflag) {
		Move();
	}

	Shot();
	effect_pdead.All();

	Draw();

	++count;
}