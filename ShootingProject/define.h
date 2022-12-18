#pragma once
#include <windows.h>

//�v���C���[�̕����X�s�[�h
#define PLAYER_SPEED 4
// �]��
#define MARGIN 10
// �w�i�̃X�N���[���X�s�[�h
#define SCROLL_SPEED 2
// �e�̍ő吔
#define PSHOT_NUM 50
#define PSHOT_SPEED 14
#define ENEMY_SNUM 50
#define ENEMY_NUM 50
#define PI 3.14

//�����蔻��p���a��`
#define PLAYER_COLLISION 2
#define ENEMY1_COLLISION 14

#define PSHOT_COLLISION 3
#define ESHOT0_COLLISION 6
#define ESHOT1_COLLISION 3
#define ESHOT2_COLLISION 2

#define PLAYER_INITX 200
#define PLAYER_INITY 420

#define EFFECT_EDEADNUM 20
#define EFFECT_PDEADNUM 20

#define GRAZE_COLLISION 10
#define GRAZE_NUM 50

#define PLAYER_LIFE 5

//�X�R�A�̕����`��̊�ƂȂ�X���W
#define SCORE_X 390

//�A�C�e���̓����蔻��p���a
#define ITEM_COLLISION 16
//�A�C�e���̑���
#define ITEM_NUM 30

#define PLAYER_PINIT 8

#define BALL_SHAKE 15

#define BALL_INITX 50
#define BALL_INITY 30

struct SHOT {
	bool flag; // �e�����˒����ǂ���
	double x;
	double y;
	int gh;
	int width, height;
	double rad;//�p�x
	int type;//�e�̎��(0�Ȃ�ʏ�A1�Ȃ�ǐՒe)
};

struct E_SHOT {
	bool flag; // �e�����˒����ǂ���
	double x;
	double y;
	double rad;
	int gh;
	int width, height;
	int pattern;
	int speed;
	bool gflag;//�O���C�Y����p�t���O
};

struct ENEMYDATA {
	int type;//�G���
	int stype;//�e���
	int m_pattern;//�ړ��p�^�[��
	int s_pattern;//���˃p�^�[��
	int in_time;//�o������
	int stop_time;//��~����
	int shot_time;//�e���ˎ���
	int out_time;//�A�Ҏ���
	int x;//x���W
	int y;//y���W
	int speed;//�e�X�s�[�h
	int hp;//HP
	int item;//�A�C�e��
};

struct PEFFECT_EXPAND {
		double x, y;
		double rad;
		int speed;
};






//���b�Z�[�W�{�b�N�X
#define MSG(m) {\
	MessageBox(NULL,m,"���b�Z�[�W",MB_OK);}

//extern�錾����key�z��ɂǂ�����ł��A�N�Z�X�ł���悤�ɂ���
extern char key[256];
extern int g_count;