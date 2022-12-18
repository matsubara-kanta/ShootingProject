#pragma once

#include "player.h"
#include "back.h"
#include "enemy.h"
#include "effect_edead.h"
#include"graze.h"
#include "score.h"
#include "item.h"
#include "boss.h"


#include <time.h>


class CONTROL {

	//プレイヤークラスのポインタ
	PLAYER* player;

	BACK* back;

	ENEMY* enemy[ENEMY_NUM];

	//敵消滅エフェクトクラス
	EFFECT_EDEAD* effect_edead[EFFECT_EDEADNUM];

	//グレイズクラス
	GRAZE* graze[GRAZE_NUM];

	SCORE* score;

	ITEM* item[ITEM_NUM];

	BOSS boss;


	//サウンドハンドル
	int s_eshot;
	int s_pshot;
	int s_edead;
	int s_pdead;
	int s_graze;
	int s_item;
	int s_bshot;

	//サウンドを鳴らすかどうかのフラグ
	bool eshot_flag;
	bool pshot_flag;
	bool edead_flag;
	bool pdead_flag;
	bool graze_flag;
	bool item_flag;
	bool bshot_flag;

	clock_t start;

	int boss_count;


	


private:
	void SoundAll();
	void EnemyCollisionAll();
	bool CircleCollision(double c1, double c2, double cx1, double cx2, double cy1, double cy2);
	void EnemyDeadEffect(double x, double y);
	void Enemy_Init();
	void BossCollisionAll();

public:
	CONTROL();
	~CONTROL();
	void All();
	void GetPlayerPosition(double* x, double* y);
	bool GetEnemyPosition(int index, double* x, double* y);
	static CONTROL& GetInstance() {
		static CONTROL control;
		return control;
	}
	void GetBossPosition(double* x, double* y);

};

