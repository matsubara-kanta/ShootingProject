#pragma once

#include "define.h"
#include "pch.h"

class BOSS {
	//���W
	double x, y, prev_x, prev_y;

	//�O���t�B�b�N�n���h��
	int gh_face[2];
	int gh_shot[3];

	//���݂̈ړ��p�^�[��
	int move_pattern;
	//���݂̃V���b�g�p�^�[��
	int shot_pattern;

	//�e�\����
	E_SHOT shot[BOSS_SHOTNUM];

	//���v�p�x�Ƒ�����
	int angle, raise;

	//���ړ����̑�����
	int raise2;
	int waitcount;
	bool wait;

	//���̈ړ��ꏊ�܂ł̋���
	double movex, movey;
	int p3_state;

	//�_���[�W�𕉂������ǂ����̃t���O
	bool damageflag;

	//�����Ă邩�ǂ����̃t���O
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

