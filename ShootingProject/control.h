#pragma once

#include "player.h"
#include "back.h"
#include "enemy.h"

#include <time.h>


class CONTROL {

	//プレイヤークラスのポインタ
	PLAYER* player;

	BACK* back;

	ENEMY* enemy[ENEMY_NUM];

	//サウンドハンドル
	int s_eshot;
	int s_pshot;
	int s_edead;

	//サウンドを鳴らすかどうかのフラグ
	bool eshot_flag;
	bool pshot_flag;
	bool edead_flag;

	clock_t start = clock();


public:
	CONTROL();
	~CONTROL();
	void SoundAll();
	void All();
	void GetPlayerPosition(double* x, double* y);
	void GetEnemyPosition(int index, double* x, double* y);
	static CONTROL& GetInstance() {
		static CONTROL control;
		return control;
	}
	bool CircleCollision(double c1, double c2, double cx1, double cx2, double cy1, double cy2);
	void CollisionAll();
};

