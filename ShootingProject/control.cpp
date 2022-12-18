#include "pch.h"
#include "control.h"

CONTROL::CONTROL()
{
	player = new PLAYER;

	back = new BACK;

	//�G�t�F�N�g�N���X�̃C���X�^���X����
	for (int i = 0; i < EFFECT_EDEADNUM; ++i) {
		effect_edead[i] = new EFFECT_EDEAD;
	}

	//�O���C�Y�N���X�̃C���X�^���X����
	for (int i = 0; i < GRAZE_NUM; ++i) {
		graze[i] = new GRAZE;
	}

	for (int i = 0; i < ITEM_NUM; ++i) {
		item[i] = new ITEM;
	}

	score = new SCORE;


	//	FILE* fp;
	//	ENEMYDATA data[ENEMY_NUM];
	//	char buf[100];
	//	int c;
	//	int col = 1;
	//	int row = 0;
	//
	//	memset(buf, 0, sizeof(buf));
	//	fp = fopen("enemydata.csv", "r");
	//
	//	if (!fp) {
	//		perror("fopen");
	//	}
	//
	//	while (fgetc(fp) != '\n');
	//
	//	while (1) {
	//
	//		while (1) {
	//
	//			c = fgetc(fp);
	//
	//			if (c == EOF)
	//				goto out;
	//
	//			if (c != ',' && c != '\n')
	//				strcat(buf, (const char*)&c);
	//			else
	//				break;
	//		}
	//
	//
	//		switch (col) {
	//		case 1: data[row].type = atoi(buf); break;
	//		case 2: data[row].stype = atoi(buf); break;
	//		case 3: data[row].m_pattern = atoi(buf); break;
	//		case 4: data[row].s_pattern = atoi(buf); break;
	//		case 5: data[row].in_time = atoi(buf); break;
	//		case 6: data[row].stop_time = atoi(buf); break;
	//		case 7: data[row].shot_time = atoi(buf); break;
	//		case 8: data[row].out_time = atoi(buf); break;
	//		case 9: data[row].x = atoi(buf); break;
	//		case 10: data[row].y = atoi(buf); break;
	//		case 11: data[row].speed = atoi(buf); break;
	//		case 12: data[row].hp = atoi(buf); break;
	//		case 13: data[row].item = atoi(buf); break;
	//		}
	//		memset(buf, 0, sizeof(buf));
	//		++col;
	//
	//		if (c == '\n') {
	//			col = 1;
	//			++row;
	//		}
	//	}
	//
	//out:
	//
	//	for (int i = 0; i < ENEMY_NUM; ++i) {
	//		enemy[i] = new ENEMY(data[i].type, data[i].stype, data[i].m_pattern, data[i].s_pattern, data[i].in_time, data[i].stop_time, data[i].shot_time,
	//			data[i].out_time, data[i].x, data[i].y, data[i].speed, data[i].hp, data[i].item);
	//	}

	Enemy_Init();

	//�T�E���h�t�@�C���ǂݍ���
	s_eshot = LoadSoundMem("SE/enemyshot.mp3");
	s_pshot = LoadSoundMem("SE/playershot.mp3");
	s_edead = LoadSoundMem("SE/edead.mp3");
	s_pdead = LoadSoundMem("SE/pdead.mp3");
	s_graze = LoadSoundMem("SE/graze.mp3");
	s_item = LoadSoundMem("SE/itemget1.mp3");
	s_bshot = s_eshot;

	eshot_flag = false;
	pshot_flag = false;
	edead_flag = false;
	pdead_flag = false;
	graze_flag = false;
	item_flag = false;
	bshot_flag = false;

	clock_t start = clock();

	boss_count = 0;

}


void CONTROL::GetPlayerPosition(double* x, double* y)
{
	double tempx, tempy;

	player->GetPosition(&tempx, &tempy);

	*x = tempx;
	*y = tempy;
}



void CONTROL::All()
{
	eshot_flag = pshot_flag = edead_flag = pdead_flag = graze_flag = item_flag = bshot_flag = false;

	SetDrawArea(MARGIN, MARGIN, MARGIN + 380, MARGIN + 460);

	back->All();
	player->All();

	if (player->GetShotSound()) {
		pshot_flag = true;
	}

	if (!boss.GetFlag()) {
		for (int i = 0; i < ENEMY_NUM; ++i) {
			if (enemy[i] != NULL) {
				//�G�V���b�g�T�E���h�t���O�`�F�b�N
				if (enemy[i]->GetShotSound()) {
					eshot_flag = true;
				}

				if (enemy[i]->All()) {
					delete enemy[i];
					enemy[i] = NULL;
					score->SetScore(TOTAL_E_NUM, 1);
					boss_count++;
					if (boss_count == 50) {
						boss.SetFlag(true);
					}
				}
			}
		}
		EnemyCollisionAll();
	}
	else {
		boss.All();
		if (boss.GetShotSound()) {
			bshot_flag = true;
		}
		BossCollisionAll();
	}


	//�O���C�Y�`��
	for (int i = 0; i < GRAZE_NUM; ++i) {
		graze[i]->All();
	}


	//�G���ŃG�t�F�N�g
	for (int i = 0; i < EFFECT_EDEADNUM; ++i) {
		if (effect_edead[i]->GetFlag()) {
			effect_edead[i]->All();
		}
	}

	//�A�C�e���`��
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (item[i]->GetFlag()) {
			item[i]->All();
		}
	}



	SetDrawArea(0, 0, 640, 480);

	score->All();



	SoundAll();

	++g_count;
}

void CONTROL::SoundAll()
{

	if (pshot_flag) {
		PlaySoundMem(s_pshot, DX_PLAYTYPE_BACK);
	}

	if (eshot_flag) {
		PlaySoundMem(s_eshot, DX_PLAYTYPE_BACK);
	}

	if (edead_flag) {
		PlaySoundMem(s_edead, DX_PLAYTYPE_BACK);
	}

	if (pdead_flag) {
		PlaySoundMem(s_pdead, DX_PLAYTYPE_BACK);
	}
	if (graze_flag) {
		PlaySoundMem(s_graze, DX_PLAYTYPE_BACK);
	}

	if (item_flag) {
		PlaySoundMem(s_item, DX_PLAYTYPE_BACK);
	}

	if (bshot_flag) {
		clock_t end = clock();

		if (300 < end - start) {
			PlaySoundMem(s_bshot, DX_PLAYTYPE_BACK);
			start = end;
		}
	}


}

bool CONTROL::CircleCollision(double c1, double c2, double cx1, double cx2, double cy1, double cy2)
{

	double hlength = c1 + c2;
	double xlength = cx1 - cx2;
	double ylength = cy1 - cy2;

	if (hlength * hlength >= xlength * xlength + ylength * ylength) {
		return true;
	}
	else {
		return false;
	}
}

void CONTROL::EnemyCollisionAll()
{
	double px, py, ex, ey;

	bool tempflag = false;
	bool gtempflag = false;

	//����L�����̒e�ƓG�Ƃ̓����蔻��
	for (int i = 0; i < PSHOT_NUM; ++i) {
		if (player->GetShotPosition(i, &px, &py)) {
			for (int s = 0; s < ENEMY_NUM; ++s) {
				//�G�N���X�̃|�C���^��NULL����Ȃ��A����deadflag��false(����łȂ����A�҂��ĂȂ�)
				if (enemy[s] != NULL && !enemy[s]->GetDeadFlag()) {
					enemy[s]->GetPosition(&ex, &ey);
					//�����蔻��
					if (CircleCollision(PSHOT_COLLISION, ENEMY1_COLLISION, px, ex, py, ey)) {
						//�������Ă���΁Adeadflag�𗧂Ă�
						enemy[s]->SetDeadFlag();
						//���������e�̃t���O��߂�
						player->SetShotFlag(i, false);
						//�G���ŉ��t���O�Z�b�g
						edead_flag = true;
						//�G���ŃG�t�F�N�g�Z�b�g
						EnemyDeadEffect(ex, ey);
						//���_��������
						score->SetScore(CURRENT_SCORE, 100);
						score->SetScore(CURRENT_E_NUM, 1);
						//�A�C�e���o��
						for (int z = 0; z < ITEM_NUM; ++z) {
							int type = enemy[s]->GetItem();
							if (!item[z]->GetFlag() && 0 <= type && type < 2) {
								item[z]->SetFlag(ex, ey, enemy[s]->GetItem());
								break;
							}
						}

					}
				}
			}
		}
	}

	//�G�̒e�Ƒ���L�����Ƃ̓����蔻��
		//�v���C���[�������Ă��
	if (!player->GetDamageFlag()) {
		player->GetPosition(&px, &py);
		for (int i = 0; i < ENEMY_NUM; ++i) {
			if (enemy[i] != NULL) {
				for (int s = 0; s < ENEMY_SNUM; ++s) {
					//�e�t���O�������Ă����true��Ԃ�
					if (enemy[i]->GetShotPosition(s, &ex, &ey)) {
						//�e�ɂ���ē����蔻�肪�Ⴄ�̂�switch���ŕ���
						switch (enemy[i]->GetShotType()) {

						case 0:
							//�O���C�Y����
							if (CircleCollision(GRAZE_COLLISION, ESHOT0_COLLISION, px, ex, py, ey)) {
								gtempflag = true;
							}

							//�������Ă��
							if (CircleCollision(PLAYER_COLLISION, ESHOT0_COLLISION, px, ex, py, ey)) {
								tempflag = true;
							}
							break;

						case 1:
							if (CircleCollision(GRAZE_COLLISION, ESHOT1_COLLISION, px, ex, py, ey)) {
								gtempflag = true;
							}

							if (CircleCollision(PLAYER_COLLISION, ESHOT1_COLLISION, px, ex, py, ey)) {
								tempflag = true;
							}
							break;

						case 2:
							if (CircleCollision(GRAZE_COLLISION, ESHOT2_COLLISION, px, ex, py, ey)) {
								gtempflag = true;
							}

							if (CircleCollision(PLAYER_COLLISION, ESHOT2_COLLISION, px, ex, py, ey)) {
								tempflag = true;
							}
							break;
						}
						//�O���C�Y�����蔻��t���O��true�Ȃ�
						if (gtempflag) {
							//�܂�
							enemy[i]->SetGrazeFlag(s);
							//�O���C�Y�̃C���X�^���X����
							for (int z = 0; z < GRAZE_NUM; ++z) {
								if (!graze[z]->GetFlag()) {
									graze[z]->SetFlag(px, py);
									break;
								}
							}
							//�O���C�Y�̓��_��������
							score->SetScore(GRAZE_SCORE, 1);
							score->SetScore(CURRENT_SCORE, 20);

							//�O���C�Y���Z�b�g
							graze_flag = true;
							gtempflag = false;
						}

						if (tempflag) {
							//����L������damageflag�𗧂Ă�
							player->SetDamageFlag();
							//�e������
							enemy[i]->SetShotFlag(s, false);
							//�v���C���[���ŉ��t���O�𗧂Ă�
							pdead_flag = true;
							//�ꎞ�t���O��߂�
							tempflag = false;
						}
					}
				}
			}
		}
		double ix, iy;

		//�A�C�e���ƃv���C���[�̓����蔻��
		for (int i = 0; i < ITEM_NUM; ++i) {
			if (item[i]->GetFlag()) {
				item[i]->GetPosition(&ix, &iy);
				if (CircleCollision(PLAYER_COLLISION, ITEM_COLLISION, px, ix, py, iy)) {
					switch (item[i]->GetType()) {
					case 0:
						score->SetScore(CURRENT_SCORE, 300);
						break;
					case 1:
						player->SetPower(1);
						score->SetScore(POWER_SCORE, player->GetPower());
						//�p���[�𑝂₷
						break;

					}
					item[i]->Delete();
					//�A�C�e���擾�����Z�b�g
					item_flag = true;
				}
			}
		}

	}
	//���C�t�͖���擾
	score->SetScore(LIFE_SCORE, player->GetLife());

}

void CONTROL::BossCollisionAll()
{

	double px = 0;
	double py = 0;
	double bx = 0;
	double by = 0;
	double ix = 0;
	double iy = 0;

	int bhp = 0;

	int itemnum = 0;

	bool hflag = false, gflag = false;

	int type;

	if (!boss.GetNodamageFlag()) {
		for (int i = 0; i < PSHOT_NUM; ++i) {
			if (player->GetShotPosition(i, &px, &py)) {
 				boss.GetPosition(&bx, &by);
				if (CircleCollision(PSHOT_COLLISION, BOSS_COLLISION, px, bx, py, by)) {
   					bhp = boss.HpSet(1);
					player->SetShotFlag(i, false);
					score->SetScore(CURRENT_SCORE, 10);

					char buf[100];
					sprintf(buf, "%d", bhp);
					SetMainWindowText(buf);


					if (BOSS_HP * 2 / 3 >= bhp && boss.GetPrevHp() > BOSS_HP * 2 / 3) {
						EnemyDeadEffect(bx, by);
						edead_flag = true;
						score->SetScore(CURRENT_SCORE, 1000);
						for (int z = 0; z < ITEM_NUM; ++z) {
							if (!item[z]->GetFlag()) {
								ix = (rand() % 100 - 51) + bx;
								iy = (rand() % 100 - 51) + by;
								item[z]->SetFlag(ix, iy, rand() % 2);
								++itemnum;
								if (itemnum == 5) {
									break;
								}
							}
						}
						boss.SetDamageSetting();
					}
					else if (BOSS_HP / 3 >= bhp && boss.GetPrevHp() > BOSS_HP / 3) {
						EnemyDeadEffect(bx, by);
						edead_flag = true;
						score->SetScore(CURRENT_SCORE, 1000);
						for (int z = 0; z < ITEM_NUM; ++z) {
							if (!item[z]->GetFlag()) {
								ix = (rand() % 100 - 51) + bx;
								iy = (rand() % 100 - 51) + by;
								item[z]->SetFlag(ix, iy, rand() % 2);
								++itemnum;
								if (itemnum == 5) {
									break;
								}
							}
						}
						boss.SetDamageSetting();
					}
					else if (bhp <= 0) {
						boss.SetFlag(false);
						EnemyDeadEffect(bx, by);
						edead_flag = true;
						score->SetScore(CURRENT_SCORE, 10000);
						for (int z = 0; z < ITEM_NUM; ++z) {
							if (!item[z]->GetFlag()) {
								ix = (rand() % 100 - 51) + bx;
								iy = (rand() % 100 - 51) + by;
								item[z]->SetFlag(ix, iy, rand() % 2);
								++itemnum;
								if (itemnum == 10) {
									break;
								}
							}
						}

					}
				}
			}
		}

	}

	if (!player->GetDamageFlag()) {
		player->GetPosition(&px, &py);
		for (int i = 0; i < BOSS_SHOTNUM; ++i) {
			if (boss.GetShotPosition(i, &bx, &by, &type)) {
				switch (type) {
				case 0:
					if (CircleCollision(GRAZE_COLLISION, ESHOT0_COLLISION, px, bx, py, by)) {
						gflag = true;
					}
					if (CircleCollision(PLAYER_COLLISION, ESHOT0_COLLISION, px, bx, py, by)) {
						hflag = true;
					}
					break;

				case 1:
					if (CircleCollision(GRAZE_COLLISION, ESHOT1_COLLISION, px, bx, py, by)) {
						gflag = true;
					}
					if (CircleCollision(PLAYER_COLLISION, ESHOT1_COLLISION, px, bx, py, by)) {
						hflag = true;
					}
					break;

				case 2:
					if (CircleCollision(GRAZE_COLLISION, ESHOT2_COLLISION, px, bx, py, by)) {
						gflag = true;
					}
					if (CircleCollision(PLAYER_COLLISION, ESHOT2_COLLISION, px, bx, py, by)) {
						hflag = true;
					}
					break;
				}
				if (gflag) {
					if (!boss.GetGrazeFlag(i)) {
						boss.SetGrazeFlag(i);
						for (int z = 0; z < GRAZE_NUM; ++z) {
							if (!graze[z]->GetFlag()) {
								graze[z]->SetFlag(px, py);
								break;

							}
						}
						score->SetScore(GRAZE_SCORE, 1);
						score->SetScore(CURRENT_SCORE, 20);
						graze_flag = true;


					}
					gflag = false;
				}
				if (hflag) {
					player->SetDamageFlag();
					boss.SetShotFlag(i, false);
					pdead_flag = true;
					hflag = false;
					break;
				}
			}
		}
	}
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (item[i]->GetFlag()) {
			item[i]->GetPosition(&ix, &iy);
			if (CircleCollision(PLAYER_COLLISION, ITEM_COLLISION, px, ix, py, iy)) {
				switch (item[i]->GetType()) {
				case 0:
					score->SetScore(CURRENT_SCORE, 300);
					break;
				case 1:
					player->SetPower(1);
					score->SetScore(POWER_SCORE, player->GetPower());
					break;
				}
				item[i]->Delete();
				item_flag = true;
			}
		}
	}
	score->SetScore(LIFE_SCORE, player->GetLife());
}

void CONTROL::EnemyDeadEffect(double x, double y)
{
	//�G�t�F�N�g�Z�b�g
	for (int z = 0; z < EFFECT_EDEADNUM; ++z) {
		if (!effect_edead[z]->GetFlag()) {
			effect_edead[z]->SetFlag(x, y);
			break;
		}
	}
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

	for (int i = 0; i < EFFECT_EDEADNUM; ++i) {
		delete effect_edead[i];
	}

	for (int i = 0; i < GRAZE_NUM; ++i) {
		delete graze[i];
	}

	delete score;

	for (int i = 0; i < ITEM_NUM; ++i) {
		delete item[i];
	}
}

bool CONTROL::GetEnemyPosition(int index, double* x, double* y)
{
	double tempx, tempy;

	if (enemy[index] == NULL || enemy[index]->GetDeadFlag())
		return false;


	//�w�肵���Y���̓G�̍��W���擾
	enemy[index]->GetPosition(&tempx, &tempy);

	//���
	*x = tempx;
	*y = tempy;

	return true;

}

void CONTROL::GetBossPosition(double* x, double* y)
{
	double bx, by;

	boss.GetPosition(&bx, &by);

	*x = bx;
	*y = by;
}


void CONTROL::Enemy_Init() {
	srand(time(NULL));

	for (int i = 0; i < ENEMY_NUM; i++) {
		int num = rand();
		// �����o��
		if (i % 3 == 2) {
			int e_num = num % 5;
			if (e_num < 2)
				e_num = 2;
			int count = 1;

			for (int j = i; j < e_num + i; j++) {
				if (j > ENEMY_NUM)
					break;
				enemy[j] = new ENEMY(num % 1, num % 3, num % 4, num % 4, (i + 1) * 60, (i + 1) * 60 + 62, (i + 1) * 60 + 61,
					(i + 1) * 60 + 141, 60 * count, -40, 6, 1, (num + j) % 2);
				count++;
			}
			i += e_num - 1;
		}
		// �P�̏o��
		else {
			enemy[i] = new ENEMY(num % 1, num % 3, num % 4, num % 4, (i + 1) * 60, (i + 1) * 60 + 60, (i + 1) * 60 + 61,
				(i + 1) * 60 + 141, 200, -40, 6, 1, num % 2);
		}
	}
}
