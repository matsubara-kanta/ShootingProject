#include "effect_edead.h"
#include "pch.h"

#include<time.h>

int EFFECT_EDEAD::gh[3] = {0,0,0};

EFFECT_EDEAD::EFFECT_EDEAD()
{
	x = y = 0;


	//画像読み込み。初回だけ
	if (gh[0] == 0) {
		gh[0] = LoadGraph("Picture/effect1.png");
		gh[1] = LoadGraph("Picture/effect2.png");
		gh[2] = LoadGraph("Picture/effect3.png");
	}
	//乱数を初期化
	srand((unsigned int)time(NULL));

	rad = 0;

	rate = 1;

	alpha = 255;

	count = 0;

	flag = false;

	index = 0;
}

void EFFECT_EDEAD::Move()
{
	if (flag) {

		//初回だけ角度と添字セット
		if (count == 0) {
			rad = rand() % 624 / 100;
			index = rand() % 3;
		}


		rate = 0.5 + count * 0.05;

		alpha = 255 - 255 / 30 * count;


		++count;

		if (count == 30) {
			count = 0;
			flag = false;
		}
	}
}

void EFFECT_EDEAD::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawRotaGraph(x, y, rate, rad, gh[index], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void EFFECT_EDEAD::All()
{
	Move();
	Draw();
}

void EFFECT_EDEAD::SetFlag(double x, double y)
{
	this->x = x;
	this->y = y;

	flag = true;
}

bool EFFECT_EDEAD::GetFlag()
{
	return flag;

}
