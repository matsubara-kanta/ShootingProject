#pragma once

class PLAYER{
private:
	//x���W,y���W
	double x,y;

	//�摜��
	int width,height;

	//�O���t�B�b�N�n���h���i�[�p�z��
	int gh[12];


	//�ړ��W��
	float move;

	//�������Əc�����̃J�E���g���B
	int xcount,ycount;
	//�Y���p�ϐ�
	int ix,iy,result;
	//�����Ă邩�ǂ����̃t���O
	bool life;

	SHOT shot[PSHOT_NUM];

	int count;
private:
	void Move();
	void Draw();
	void Shot();


public:
	PLAYER();
	void All();

};