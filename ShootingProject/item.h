#pragma once
#include "pch.h"

class ITEM {
private:
	//�O���t�B�b�N�n���h��
	static int gh[2], ghs[2];

	//�ǂ����̃A�C�e�����������ϐ�
	int type;

	//���W
	double x, y;
	double prev_y;

	//��]�p�x
	double rad;

	//�J�E���g
	int count;

	//�A�C�e�����������n�߂�t���O
	bool fall_flag;

	//�o�������ǂ����̃t���O
	bool flag;

private:
	void Move();
	void Draw();
public:
	ITEM();
	void SetFlag(double x, double y, int type);
	bool GetFlag();
	void Delete();
	void GetPosition(double* x, double* y);
	int  GetType();
	void All();
};

