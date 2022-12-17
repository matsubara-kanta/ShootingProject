#include "enemy.h"
#include "pch.h"
#include "control.h"

#include <math.h>
#include <time.h>

ENEMY::ENEMY(int type, int stype, int m_pattern, int s_pattern, int in_time, int stop_time, int shot_time, int out_time, int x, int y, int speed, int hp, int item)
{

	width = 27;
	height = 25;

	this->type = type;
	this->stype = stype;

	this->m_pattern = m_pattern;
	this->s_pattern = s_pattern;

	this->x = x;
	this->y = y;

	this->in_time = in_time;
	this->stop_time = stop_time;
	this->shot_time = shot_time;
	this->out_time = out_time;

	//hpとアイテム代入
	this->hp = hp;
	this->item = item;

	//敵画像読み込み
	if (type == 0) {
		LoadDivGraph("Picture/enemy.png", 3, 1, 3, 27, 25, gh);
	}


	int temp = -1;
	//弾画像読み込み
	switch (stype) {
	case 0:
		temp = LoadGraph("Picture/enemyshot1.png");
		break;
	case 1:
		temp = LoadGraph("Picture/enemyshot2.png");
		break;
	case 2:
		temp = LoadGraph("Picture/enemyshot3.png");
		break;

	}

	int w, h;
	GetGraphSize(temp, &w, &h);


	for (int i = 0; i < ENEMY_SNUM; ++i) {
		shot[i].flag = false;
		shot[i].gh = temp;
		shot[i].width = w;
		shot[i].height = h;
		shot[i].pattern = s_pattern;
		shot[i].speed = speed;
		shot[i].x = x;
		shot[i].y = y;
		shot[i].flag = false;
	}


	count = 0;
	scount = 0;
	num = 0;
	rad = 0;

	deadflag = false;
	endflag = false;
	sflag = false;

}

void ENEMY::Move() {
	//まだ生きてるか画面内に居るときだけ処理
	if (!deadflag) {
		switch (m_pattern) {
			//途中で止まって、そのまま後ろに帰るパターン
		case 0:

			//出てきてから止まる時間までの間なら下に移動
			if (in_time < g_count && g_count < stop_time) {
				y += 2;
				//帰還時間を過ぎたら戻る。
			}
			else if (g_count > out_time) {
				y -= 2;
			}
			break;

			//そのまま止まらずに下に行くパターン
		case 1:

			if (in_time <= g_count) {
				y += 2;
			}

			break;

			//ちょっとずつ左に移動しながら消えていく
		case 2:
			if (in_time <= g_count) {
				y += 1;
				if (count % 10 == 0) {
					x -= 1;
				}
			}
			break;

			//ちょっとずつ右に移動しながら消えていく
		case 3:
			if (in_time <= g_count) {
				y += 1;
				if (count % 10 == 0) {
					x += 1;
				}
			}
			break;

		}
		//画面からはみ出したら、deadflag(はみ出すか死ぬかのフラグ)をtrueにする。
		if (g_count >= stop_time) {
			if (OutCheck()) {
				deadflag = true;
			}
		}
		++count;
	}
}


void ENEMY::Draw() {
	int temp;

	//弾から最初に描画
	for (int i = 0; i < ENEMY_SNUM; ++i) {
		if (shot[i].flag) {
			if (stype == 0 || stype == 2) {
				DrawGraph(shot[i].x - shot[i].width / 2, shot[i].y - shot[i].height / 2, shot[i].gh, true);
			}
			else {
				DrawRotaGraph(shot[i].x, shot[i].y, 1.0, shot[i].rad + (90 * PI / 180), shot[i].gh, true);
			}
		}
	}



	if (!deadflag) {
		temp = count % 40 / 10;
		if (temp == 3)
			temp = 1;

		DrawGraph(x - width / 2, y - height / 2, gh[temp], TRUE);

	}
}

void ENEMY::Shot()
{

	//CONTROLクラスの参照
	CONTROL& control = CONTROL::GetInstance();
	double px, py;


	//発射タイミングになったら、フラグを立てる
	if (shot_time == g_count) {
		sflag = true;
	}

	//ショット音フラグを戻す
	s_shot = false;

	//フラグ立ってるときだけ
	if (sflag) {

		if (!deadflag) {
			//プレイヤーの一取得
			control.GetPlayerPosition(&px, &py);

			//敵とプレイヤーとの座標の差から逆正接を求める。
			//初回だけ実行
			if (scount == 0)
				rad = atan2(py - y, px - x);


			switch (s_pattern) {
				//前方にショット
			case 0:
				//5ループに一回発射。20までなので5発発射。
				if (scount % 5 == 0 && scount <= 20) {
					for (int i = 0; i < ENEMY_SNUM; ++i) {
						//フラグが立ってない弾を探して、座標等をセット
						if (shot[i].flag == false) {
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
							shot[i].rad = rad;
							break;
						}
					}
					//ショットサウンドフラグを立てる
					s_shot = true;
				}
				break;


				//プレイヤーに向かって直線ショット
			case 1:
				//6ループに一回発射。54までなので10発発射。
				if (scount % 6 == 0 && scount <= 54) {
					for (int i = 0; i < ENEMY_SNUM; ++i) {
						//フラグが立ってない弾を探して、座標等をセット
						if (shot[i].flag == false) {
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
							shot[i].rad = rad;
							break;
						}
					}
					//ショットサウンドフラグを立てる
					s_shot = true;

				}
				break;

				//3直線ショット
			case 2:
				//10ループに一回発射。1ループに3発なので5ループさせると１５発発射
				if (scount % 10 == 0 && scount <= 40) {
					for (int i = 0; i < ENEMY_SNUM; ++i) {
						//フラグが立ってない弾を探して、座標等をセット
						if (shot[i].flag == false) {
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;

							//0はキャラクターに向かって発射
							if (num == 0) {

								//敵とプレイヤーとの逆正接から30度引いたラジアンを代入
								shot[i].rad = rad - (10 * 3.14 / 180);

							}
							else if (num == 1) {
								//敵とプレイヤーとの逆正接を代入
								shot[i].rad = rad;

							}
							else if (num == 2) {
								//敵とプレイヤーとの逆正接から30度足したラジアンを代入
								shot[i].rad = rad + (10 * PI / 180);

							}
							++num;

							//3発発射したら,numを0にしてループを抜ける。
							if (num == 3) {
								num = 0;
								break;
							}
						}
					}
					//ショットサウンドフラグを立てる
					s_shot = true;

				}
				break;

				//乱射ショット
			case 3:
				//10ループに一回発射。42までなので15発発射。
				if (scount % 3 == 0 && scount <= 42) {
					for (int i = 0; i < ENEMY_SNUM; ++i) {
						//フラグが立ってない弾を探して、座標等をセット
						if (shot[i].flag == false) {
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
							//初回だけ乱数初期化
							if (num == 0)
								srand((unsigned int)time(NULL));

							shot[i].rad = atan2(py - y, px - x) - (60 * PI / 180) + ((rand() % 120) * PI / 180);
							++num;
							break;
						}
					}
					//ショットサウンドフラグを立てる
					s_shot = true;

				}
				break;

			}
		}


		//フラグが立ってる弾の数
		int s = 0;

		//フラグ立ってる弾だけ、弾の移動を行う
		for (int i = 0; i < ENEMY_SNUM; ++i) {
			if (shot[i].flag) {
				switch (shot[i].pattern) {
					//単純に下に発射
				case 0:
					shot[i].y += shot[i].speed;
					break;

				case 1:
					shot[i].x += shot[i].speed * cos(shot[i].rad);
					shot[i].y += shot[i].speed * sin(shot[i].rad);
					break;
				case 2:
					shot[i].x += shot[i].speed * cos(shot[i].rad);
					shot[i].y += shot[i].speed * sin(shot[i].rad);
					break;
				case 3:
					shot[i].x += shot[i].speed * cos(shot[i].rad);
					shot[i].y += shot[i].speed * sin(shot[i].rad);
					break;

				}

				//弾が画面をはみ出たらフラグを戻す。
				if (ShotOutCheck(i)) {
					shot[i].flag = false;
					continue;
				}
				++s;
			}
		}
		//sがゼロということは発射中の弾がない。
		//かつdeadflagがTRUEということはこの敵のクラスは消滅させてもよい
		if (s == 0 && deadflag) {
			//敵クラス消滅フラグをTRUEにする
			endflag = true;
		}

		++scount;

	}

}

bool ENEMY::OutCheck()
{
	if (x < -50 || x>520 || y < -50 || y>530) {
		return true;
	}
	else {
		return false;
	}
}

bool ENEMY::ShotOutCheck(int i)
{
	//弾が画面をはみ出たらフラグを戻す。
	if (shot[i].x < -20 || shot[i].x>420 || shot[i].y < -20 || shot[i].y>500) {
		return true;
	}
	else {
		return false;
	}
}

void ENEMY::GetPosition(double* x, double* y)
{
	*x = this->x;
	*y = this->y;

}

bool ENEMY::GetShotPosition(int index, double* x, double* y)
{
	if (shot[index].flag) {
		*x = shot[index].x;
		*y = shot[index].y;
		return true;
	}
	else {
		return false;
	}
}

void ENEMY::SetShotFlag(int index, bool flag)
{
	shot[index].flag = flag;
}

int ENEMY::GetShotType()
{
	return stype;
}



void ENEMY::SetDeadFlag()
{
	deadflag = true;
}

bool ENEMY::GetDeadFlag()
{
	return deadflag;
}


bool ENEMY::GetShotSound()
{
	return s_shot;
}

void ENEMY::SetGrazeFlag(int index)
{
	shot[index].gflag = true;
}

bool ENEMY::GetGrazeFlag(int index)
{
	return shot[index].gflag;
}




bool ENEMY::All() {
	Move();
	Shot();
	Draw();
	++count;
	return endflag;
}