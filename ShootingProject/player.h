#pragma once
#include "effect_pdead.h"
#include "ball.h"


class PLAYER {
private:
	//x座標,y座標
	double x, y;

	//画像幅
	int width, height;

	//グラフィックハンドル格納用配列
	int gh[12];


	//移動係数
	float move;

	//横方向と縦方向のカウント数。
	int xcount, ycount;
	//添字用変数
	int ix, iy, result;
	//生きてるかどうかのフラグ
	int life;
	bool damageflag;
	bool endflag;
	//ダメージ中のカウント
	int dcount;


	SHOT shot[PSHOT_NUM];

	int count;

	bool s_shot;

	EFFECT_PDEAD effect_pdead;

	int power;

	BALL ball;





private:
	void Move();
	void Draw();
	void Shot();
	void Ball();
	void BallShotSet(int index);
	int NearEnemySearch();



public:
	PLAYER();
	bool GetShotSound();
	bool GetShotPosition(int index, double* x, double* y);
	void SetShotFlag(int index, bool flag);
	void GetPosition(double* x, double* y);
	void SetDamageFlag();
	bool GetDamageFlag();
	int GetLife();
	void SetPower(int p);
	int  GetPower();
	void All();

};