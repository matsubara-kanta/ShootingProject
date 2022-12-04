#include "pch.h"
#include "control.h"
#include <stdio.h>

CONTROL::CONTROL()
{
	//�v���C���[�N���X�̐���
	player = new PLAYER;

	back = new BACK;

	FILE* fp;
	ENEMYDATA data[ENEMY_NUM];
	char buf[100];
	int c;
	int col = 1;
	int row = 0;

	memset(buf, 0, sizeof(buf));
	fp = fopen("enemydata.csv", "r");

	if (!fp) {
		perror("fopen");
	}

	//�w�b�_�ǂݔ�΂�
	while (fgetc(fp) != '\n');

	while (1) {
		printf("fileopen");

		while (1) {

			c = fgetc(fp);
			//�����Ȃ烋�[�v�𔲂���B
			if (c == EOF)
				goto out;
			printf("%d", c);
			//�J���}�����s�łȂ���΁A�����Ƃ��ĂȂ���
			if (c != ',' && c != '\n')
				strcat(buf, (const char*)&c);
			//�J���}�����s�Ȃ烋�[�v������B
		}
		printf("%s",buf);

		//�����ɗ����Ƃ������Ƃ́A1�Z�����̕����񂪏o���オ�����Ƃ�������
		switch (col) {
			//1��ڂ͓G��ނ�\���Batoi�֐��Ő��l�Ƃ��đ���B
		case 1: data[row].type = atoi(buf); break;
			//2��ڂ͒e��ށB�ȍ~�ȗ��B
		case 2: data[row].stype = atoi(buf); break;
		case 3: data[row].m_pattern = atoi(buf); break;
		case 4: data[row].s_pattern = atoi(buf); break;
		case 5: data[row].in_time = atoi(buf); break;
		case 6: data[row].stop_time = atoi(buf); break;
		case 7: data[row].shot_time = atoi(buf); break;
		case 8: data[row].out_time = atoi(buf); break;
		case 9: data[row].x = atoi(buf); break;
		case 10: data[row].y = atoi(buf); break;
		case 11: data[row].speed = atoi(buf); break;
		case 12: data[row].hp = atoi(buf); break;
		case 13: data[row].item = atoi(buf); break;
		}
		//�o�b�t�@�������
		memset(buf, 0, sizeof(buf));
		//�񐔂𑫂�
		++col;

		//����ǂݍ��񂾕��������s��������񐔂���������čs���𑝂₷
		if (c == '\n') {
			col = 1;
			++row;
		}
	}
out:

	//�G�N���X����
	for (int i = 0; i < ENEMY_NUM; ++i) {
		enemy[i] = new ENEMY(data[i].type, data[i].stype, data[i].m_pattern, data[i].s_pattern, data[i].in_time, data[i].stop_time, data[i].shot_time,
			data[i].out_time, data[i].x, data[i].y, data[i].speed, data[i].hp, data[i].item);
	}

}

void CONTROL::All()
{
	SetDrawArea(MARGIN, MARGIN, MARGIN + 380, MARGIN + 460);

	back->All();
	//�v���C���[�N���X��All�֐����s
	player->All();

	for (int i = 0; i < ENEMY_NUM; ++i) {
		if (enemy[i] != NULL) {
			if (enemy[i]->All()) {
				delete enemy[i];
				enemy[i] = NULL;
			}
		}
	}

	++g_count;
}

CONTROL::~CONTROL()
{
	delete player;
	delete back;

	for (int i = 0; i < ENEMY_NUM; ++i) {
		if (enemy[i] != NULL) {
			delete enemy[i];
		}
	}
}
