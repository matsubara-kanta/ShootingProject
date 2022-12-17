#pragma once
#include "pch.h"

class ENEMY {
private:
	double x, y;
	int gh[3];
	int width, height;
	int in_time, stop_time, out_time, shot_time;
	int type;
	int stype;
	int m_pattern;
	int s_pattern;
	int hp;
	int item;
	int count;
	int num;
	double rad;
	bool deadflag;
	bool endflag;
	E_SHOT shot[ENEMY_SNUM];
	bool sflag;
	int scount;
	bool s_shot;

private:
	void Move();
	void Shot();
	void Draw();
	bool OutCheck();
	bool ShotOutCheck(int i);



public:
	bool All();
	void GetPosition(double* x, double* y);
	ENEMY(int type, int stype, int m_pattern, int s_pattern, int in_time, int stop_time, int shot_time, int out_time, int x, int y, int speed, int hp, int item);
	bool GetShotSound();
	void SetDeadFlag();
	bool GetDeadFlag();
	bool GetShotPosition(int index, double* x, double* y);
	void SetShotFlag(int index, bool flag);
	int GetShotType();
	int  GetItem();
	void SetGrazeFlag(int index);
	bool GetGrazeFlag(int index);
};