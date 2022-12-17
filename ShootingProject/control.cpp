#include "pch.h"
#include "control.h"

#include <stdio.h>

CONTROL::CONTROL()
{
	player = new PLAYER;

	back = new BACK;

	//エフェクトクラスのインスタンス生成
	for (int i = 0; i < EFFECT_EDEADNUM; ++i) {
		effect_edead[i] = new EFFECT_EDEAD;
	}

	//グレイズクラスのインスタンス生成
	for (int i = 0; i < GRAZE_NUM; ++i) {
		graze[i] = new GRAZE;
	}


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

	//サウンドファイル読み込み
	s_eshot = LoadSoundMem("SE/enemyshot.mp3");
	s_pshot = LoadSoundMem("SE/playershot.mp3");
	s_edead = LoadSoundMem("SE/edead.mp3");
	s_pdead = LoadSoundMem("SE/pdead.mp3");
	s_graze = LoadSoundMem("SE/graze.mp3");

	eshot_flag = false;
	pshot_flag = false;
	edead_flag = false;
	pdead_flag = false;
	graze_flag = false;

}




void CONTROL::GetPlayerPosition(double* x, double* y)
{
	double tempx, tempy;

	player->GetPosition(&tempx, &tempy);

	*x = tempx;
	*y = tempy;
}

void CONTROL::GetEnemyPosition(int index, double* x, double* y)
{
	double tempx, tempy;
	//指定した添字の敵の座標を取得
	enemy[index]->GetPosition(&tempx, &tempy);

	//代入
	*x = tempx;
	*y = tempy;
}



void CONTROL::All()
{
	eshot_flag = pshot_flag = edead_flag = pdead_flag = graze_flag = false;

	SetDrawArea(MARGIN, MARGIN, MARGIN + 380, MARGIN + 460);

	back->All();
	player->All();

	if (player->GetShotSound()) {
		pshot_flag = true;
	}


	for (int i = 0; i < ENEMY_NUM; ++i) {
		if (enemy[i] != NULL) {
			//敵ショットサウンドフラグチェック
			if (enemy[i]->GetShotSound()) {
				eshot_flag = true;
			}

			if (enemy[i]->All()) {
				delete enemy[i];
				enemy[i] = NULL;
			}
		}
	}

	CollisionAll();

	//グレイズ描画
	for (int i = 0; i < GRAZE_NUM; ++i) {
		graze[i]->All();
	}


	//敵消滅エフェクト
	for (int i = 0; i < EFFECT_EDEADNUM; ++i) {
		if (effect_edead[i]->GetFlag()) {
			effect_edead[i]->All();
		}
	}


	SoundAll();

	++g_count;
}

void CONTROL::SoundAll()
{

	if (pshot_flag) {
		PlaySoundMem(s_pshot, DX_PLAYTYPE_BACK);
	}

	if (eshot_flag) {
		clock_t end = clock();
		if (200 < end - start)
			PlaySoundMem(s_eshot, DX_PLAYTYPE_BACK);
		start = end;
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

void CONTROL::CollisionAll()
{
	double px, py, ex, ey;

	bool tempflag = false;
	bool gtempflag = false;

	//操作キャラの弾と敵との当たり判定
	for (int i = 0; i < PSHOT_NUM; ++i) {
		if (player->GetShotPosition(i, &px, &py)) {
			for (int s = 0; s < ENEMY_NUM; ++s) {
				//敵クラスのポインタがNULLじゃない、かつdeadflagがfalse(死んでない＆帰還してない)
				if (enemy[s] != NULL && !enemy[s]->GetDeadFlag()) {
					enemy[s]->GetPosition(&ex, &ey);
					//当たり判定
					if (CircleCollision(PSHOT_COLLISION, ENEMY1_COLLISION, px, ex, py, ey)) {
						//当たっていれば、deadflagを立てる
						enemy[s]->SetDeadFlag();
						//当たった弾のフラグを戻す
						player->SetShotFlag(i, false);
						//敵消滅音フラグセット
						edead_flag = true;
						//敵消滅エフェクトセット
						EnemyDeadEffect(ex, ey);
					}
				}
			}
		}
	}

	//敵の弾と操作キャラとの当たり判定
		//プレイヤーが生きてれば
	if (!player->GetDamageFlag()) {
		player->GetPosition(&px, &py);
		for (int i = 0; i < ENEMY_NUM; ++i) {
			if (enemy[i] != NULL) {
				for (int s = 0; s < ENEMY_SNUM; ++s) {
					//弾フラグが立っていればtrueを返す
					if (enemy[i]->GetShotPosition(s, &ex, &ey)) {
						//弾によって当たり判定が違うのでswitch文で分岐
						switch (enemy[i]->GetShotType()) {

						case 0:
							//グレイズ判定
							if (CircleCollision(GRAZE_COLLISION, ESHOT0_COLLISION, px, ex, py, ey)) {
								gtempflag = true;
							}

							//当たってれば
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
						//グレイズ当たり判定フラグがtrueなら
						if (gtempflag) {
							//まだ
							enemy[i]->SetGrazeFlag(s);
							//グレイズのインスタンス検索
							for (int z = 0; z < GRAZE_NUM; ++z) {
								if (!graze[z]->GetFlag()) {
									graze[z]->SetFlag(px, py);
									break;
								}
							}
							//グレイズ音セット
							graze_flag = true;
							gtempflag = false;
						}


						if (tempflag) {
							//操作キャラのdamageflagを立てる
							player->SetDamageFlag();
							//弾を消す
							enemy[i]->SetShotFlag(s, false);
							//プレイヤー消滅音フラグを立てる
							pdead_flag = true;
							//一時フラグを戻す
							tempflag = false;
						}
					}
				}
			}
		}
	}

}

void CONTROL::EnemyDeadEffect(double x, double y)
{
	//エフェクトセット
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

}
