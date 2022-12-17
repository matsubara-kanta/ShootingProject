#include "pch.h"
#include "control.h"
#include <stdio.h>

CONTROL::CONTROL()
{
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

	while (fgetc(fp) != '\n');

	while (1) {

		while (1) {

			c = fgetc(fp);

			if (c == EOF)
				goto out;

			if (c != ',' && c != '\n')
				strcat(buf, (const char*)&c);
			else
				break;
		}


		switch (col) {
		case 1: data[row].type = atoi(buf); break;
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
		memset(buf, 0, sizeof(buf));
		++col;

		if (c == '\n') {
			col = 1;
			++row;
		}
	}

out:

	for (int i = 0; i < ENEMY_NUM; ++i) {
		enemy[i] = new ENEMY(data[i].type, data[i].stype, data[i].m_pattern, data[i].s_pattern, data[i].in_time, data[i].stop_time, data[i].shot_time,
			data[i].out_time, data[i].x, data[i].y, data[i].speed, data[i].hp, data[i].item);
	}

}

void CONTROL::All()
{
	SetDrawArea(MARGIN, MARGIN, MARGIN + 380, MARGIN + 460);

	back->All();
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
