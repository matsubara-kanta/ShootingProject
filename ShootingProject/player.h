#pragma once
#include "effect_pdead.h"

class PLAYER {
private:
	//x���W,y���W
	double x, y;

	//�摜��
	int width, height;

	//�O���t�B�b�N�n���h���i�[�p�z��
	int gh[12];


	//�ړ��W��
	float move;

	//�������Əc�����̃J�E���g���B
	int xcount, ycount;
	//�Y���p�ϐ�
	int ix, iy, result;
	//�����Ă邩�ǂ����̃t���O
	int life;
	bool damageflag;
	bool endflag;
	//�_���[�W���̃J�E���g
	int dcount;


	SHOT shot[PSHOT_NUM];

	int count;

	bool s_shot;

	EFFECT_PDEAD effect_pdead;



private:
	void Move();
	void Draw();
	void Shot();


public:
	PLAYER();
	bool GetShotSound();
	bool GetShotPosition(int index, double* x, double* y);
	void SetShotFlag(int index, bool flag);
	void GetPosition(double* x, double* y);
	void SetDamageFlag();
	bool GetDamageFlag();
	int GetLife();
	void All();

};