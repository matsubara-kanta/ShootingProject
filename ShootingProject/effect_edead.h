#pragma once

class EFFECT_EDEAD {

private:
	//���W
	double x, y;

	//�O���t�B�b�N�n���h��
	static int gh[3];

	//�G�t�F�N�g�摜�̊p�x
	double rad;

	//�g�嗦
	double rate;

	//�����x
	int alpha;

	//�ǂ̉摜���g�����̓Y��
	int index;

	//�J�E���g
	int count;

	//���s�����ǂ����̃t���O
	bool flag;
private:
	void Move();
	void Draw();
public:
	EFFECT_EDEAD();
	bool GetFlag();
	void SetFlag(double x, double y);
	void All();
};