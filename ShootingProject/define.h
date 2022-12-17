#pragma once
#include <windows.h>

//�v���C���[�̕����X�s�[�h
#define PLAYER_SPEED 4
// �]��
#define MARGIN 10
// �w�i�̃X�N���[���X�s�[�h
#define SCROLL_SPEED 2
// �e�̍ő吔
#define PSHOT_NUM 20
#define PSHOT_SPEED 14
#define ENEMY_SNUM 50
#define ENEMY_NUM 5
#define PI 3.1415926535897932384626433832795f

//�����蔻��p���a��`
#define PLAYER_COLLISION 6
#define ENEMY1_COLLISION 14

#define PSHOT_COLLISION 3
#define ESHOT1_COLLISION 12
#define ESHOT2_COLLISION 3
#define ESHOT3_COLLISION 2



struct SHOT {
	bool flag; // �e�����˒����ǂ���
	double x;
	double y;
	int gh;
	int width, height;
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


//���b�Z�[�W�{�b�N�X
#define MSG(m) {\
	MessageBox(NULL,m,"���b�Z�[�W",MB_OK);}

//extern�錾����key�z��ɂǂ�����ł��A�N�Z�X�ł���悤�ɂ���
extern char key[256];
extern int g_count;