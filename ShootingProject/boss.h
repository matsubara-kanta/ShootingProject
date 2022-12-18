#pragma once

#include "define.h"
#include "pch.h"

class BOSS {
	//座標
	double x, y, prev_x, prev_y;

	//グラフィックハンドル
	int gh_face[2];
	int gh_shot[3];

	//現在の移動パターン
	int move_pattern;
	//現在のショットパターン
	int shot_pattern;

	//弾構造体
	E_SHOT shot[BOSS_SHOTNUM];

	//合計角度と増加量
	int angle, raise;

	//横移動時の増加量
	int raise2;
	int waitcount;
	bool wait;

	//次の移動場所までの距離
	double movex, movey;
	int p3_state;

	//ダメージを負ったかどうかのフラグ
	bool damageflag;

	//生きてるかどうかのフラグ
	bool flag;

	bool shotflag;

	int count;
	int scount;
	int temp_scount;

	bool s_shot;

	int hp;

	int prev_hp;

	bool no_damage;

	int prev_move_pattern;
	int prev_shot_pattern;

	clock_t start;

private:
	void Move();
	void Appear();
	void MovePattern1();
	void MovePattern2();
	void MovePattern3();
	void MoveInit(double bx, double by, int state);
	void Draw();
	void Shot();
	bool ShotOutCheck(int i);
	int ShotSearch();
	void MoveToDefault();
	void SetMovePattern(int pattern);
	void SetShotPattern(int pattern);

public:
	BOSS();
	void SetDamageFlag();
	void SetFlag(bool f);
	bool GetFlag();
	void All();
	bool GetGrazeFlag(int index);
	void SetGrazeFlag(int index);
	bool GetShotSound();
	void GetPosition(double* x, double* y);
	bool GetShotPosition(int index, double* x, double* y, int* type);
	int  HpSet(int damage);
	void SetShotFlag(int index, bool flag);
	bool GetNodamageFlag();
	void SetDamageSetting();
	int GetPrevHp();
};

