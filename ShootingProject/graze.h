#pragma once

class GRAZE {
private:
	//�O���t�B�b�N�n���h��
	static int gh;

	//���W
	double x, y;

	//�p�x
	double rad;

	//�A���t�@�l
	int alpha;

	//�g�嗦
	double rate;

	//�J�E���g
	int count;

	//���s�����ǂ����̃t���O
	bool flag;

private:
	void Move();
	void Draw();
public:
	GRAZE();
	void SetFlag(double x, double y);
	bool GetFlag();
	void All();
};
