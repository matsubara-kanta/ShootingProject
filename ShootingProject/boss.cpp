#include "boss.h"
#include "pch.h"
#include "control.h"

//�R���X�g���N�^
BOSS::BOSS()
{
	//���W�����l
	x = 200;
	y = -100;
	prev_x = 200;
	prev_y = -100;

	//�摜�ǂݍ���
	gh_face[0] = LoadGraph("Picture/boss.png");
	gh_face[1] = LoadGraph("Picture/boss_damage.png");

	gh_shot[0] = LoadGraph("Picture/enemyshot1.png");
	gh_shot[1] = LoadGraph("Picture/enemyshot2.png");
	gh_shot[2] = LoadGraph("Picture/enemyshot3.png");

	//�e������
	for (int i = 0; i < BOSS_SHOTNUM; ++i) {
		shot[i].flag = false;
		shot[i].gflag = false;
		shot[i].gh = 0;
		shot[i].pattern = 0;
		shot[i].rad = 0;
		shot[i].speed = 0;
		shot[i].x = 0;
		shot[i].y = 0;
		shot[i].type = 0;
	}

	raise = 2;
	raise2 = 2;
	angle = 0;
	move_pattern = 0;
	shot_pattern = 0;

	movex = 0;
	movey = 180;

	waitcount = 0;
	wait = false;
	p3_state = 0;

	damageflag = false;
	flag = false;
	shotflag = false;

	count = 0;
	scount = 0;
	temp_scount = 0;

	s_shot = false;

	hp = BOSS_HP;

	no_damage = false;

	clock_t start = clock();
}

void BOSS::Move()
{

	switch (move_pattern) {
	case 0:
		Appear();
		break;
	case 1:
		MovePattern1();
		break;
	case 2:
		MovePattern2();
		break;
	case 3:
		MovePattern3();
		break;
	case 4:
		MoveToDefault();
		break;

	}
}

void BOSS::Appear()
{
	double temp;

	angle += 2;

	temp = sin(angle * PI / 180);

	x = 200;
	y = prev_y + temp * movey;

	//��ʒu�܂ňړ�������ړ��p�^�[����1�ɕύX
	if (angle == 90) {
		move_pattern = 1;
		angle = 0;
		shotflag = true;
	}
}

void BOSS::MovePattern1()
{
	angle += raise;

	y = 80 + sin(angle * PI / 180) * BOSS_SHAKE;

	if (angle == 90) {
		raise = -2;
	}
	else if (angle == -90) {
		raise = 2;
	}

	x = 200;
}

void BOSS::MovePattern2()
{
	if (!wait) {

		x += raise2;

		if (x == 70) {
			raise2 = 2;
			wait = true;
		}
		else if (x == 330) {
			raise2 = -2;
			wait = true;
		}
	}

	if (wait) {
		++waitcount;
		if (waitcount == 20) {
			wait = false;
			waitcount = 0;
		}
	}
}

void BOSS::MovePattern3()
{

	double temp;

	angle += 2;

	temp = sin(angle * PI / 180);

	x = prev_x + temp * movex;
	y = prev_y + temp * movey;

	if (angle == 90) {

		if (p3_state == 0) {
			MoveInit(70, 80, 1);
		}
		else if (p3_state == 1) {
			MoveInit(200, 160, 2);
		}
		else if (p3_state == 2) {
			MoveInit(330, 80, 0);
		}
	}

}

void BOSS::MoveInit(double bx, double by, int state)
{

	prev_x = x;
	prev_y = y;

	movex = bx - x;
	movey = by - y;

	angle = 0;

	p3_state = state;
}

void BOSS::Shot()
{
	//�������˂�����
	int num = 0;
	//�󂢂Ă�e�̓Y����
	int index;

	//scount��߂����ǂ����̃t���O
	bool scflag = false;


	CONTROL& control = CONTROL::GetInstance();

	double px, py;
	static double trad;

	if (!damageflag) {


		control.GetPlayerPosition(&px, &py);

		if (scount == 0)
			trad = atan2(py - y, px - x);

		//�T�E���h�t���O��߂�
		s_shot = false;

		//�e�̃Z�b�g
		switch (shot_pattern) {

		case 0:
			if (scount % 5 == 0 && scount <= 15) {

				while ((index = ShotSearch()) != -1) {
					shot[index].gh = gh_shot[1];
					shot[index].pattern = 0;
					shot[index].speed = 6;

					if (num == 0) {
						shot[index].rad = trad - (10 * PI / 180);
					}
					else if (num == 1) {
						shot[index].rad = trad - (5 * PI / 180);
					}
					else if (num == 2) {
						shot[index].rad = trad;
					}
					else if (num == 3) {
						shot[index].rad = trad + (5 * PI / 180);
					}
					else if (num == 4) {
						shot[index].rad = trad + (10 * PI / 180);
					}

					++num;

					s_shot = true;

					if (num == 5) {
						break;
					}
				}
			}

			break;
		case 1:
			if (scount % 5 == 0) {
				if ((index = ShotSearch()) != -1) {
					shot[index].gh = gh_shot[2];
					shot[index].speed = 4;
					shot[index].rad = atan2(py - y, px - x) + (rand() % 41 - 20) * PI / 180;
					shot[index].pattern = 1;

					s_shot = true;

				}
			}
			break;


		case 2:
			if (scount % 10 == 0) {
				trad = atan2(py - y, px - x);
				while ((index = ShotSearch()) != -1) {

					shot[index].gh = gh_shot[0];
					shot[index].type = 0;
					shot[index].speed = 5;
					shot[index].rad = trad + num * ((360 / 20) * PI / 180);
					shot[index].pattern = 2;

					++num;

					if (num == 20) {
						break;
					}
					s_shot = true;
				}
			}
		case 3:
			if (scount % 15 == 0) {

				while ((index = ShotSearch()) != -1) {
					shot[index].gh = gh_shot[0];
					shot[index].type = 0;
					shot[index].speed = 3;
					shot[index].pattern = 3;
					shot[index].rad = ((360 / 20) * PI / 180) * num + ((scount / 15) * 0.08);


					++num;

					if (num == 20) {
						break;
					}
					s_shot = true;
				}
			}
			//num = 0;
			//if (scount % 5 == 0 && temp_scount <= scount) {

			//	while ((index = ShotSearch()) != -1) {
			//		shot[index].gh = gh_shot[1];
			//		shot[index].type = 1;
			//		shot[index].speed = 6;
			//		shot[index].pattern = 3;
			//		if (num == 0) {
			//			shot[index].x = x - 50;
			//			shot[index].rad = atan2(py - y, px - (x - 50));
			//		}
			//		else if (num == 1) {
			//			shot[index].x = x + 50;
			//			shot[index].rad = atan2(py - y, px - (x + 50));
			//		}



			//		++num;

			//		if (num == 2) {
			//			if (temp_scount + 20 == scount) {
			//				temp_scount += 60;
			//			}
			//			break;
			//		}
			//		s_shot = true;
			//	}
			//}
			break;
		default:
			break;
		}

		for (int i = 0; i < BOSS_SHOTNUM; ++i) {
			if (shot[i].flag) {
				switch (shot[i].pattern) {

				case 0:
					shot[i].x += shot[i].speed * cos(shot[i].rad);
					shot[i].y += shot[i].speed * sin(shot[i].rad);

					if (scflag == false && scount == 40) {
						scflag = true;
					}

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

				if (ShotOutCheck(i)) {
					shot[i].flag = false;
				}
			}
		}

		++scount;

		if (scflag) {
			scount = 0;
		}

	}

}

int BOSS::ShotSearch()
{
	bool check = false;
	int i;

	for (i = 0; i < BOSS_SHOTNUM; ++i) {
		if (shot[i].flag == false) {
			check = true;
			break;
		}
	}
	if (check) {
		shot[i].flag = true;
		shot[i].x = x;
		shot[i].y = y;
	}
	else {
		i = -1;
	}

	return i;
}


void BOSS::Draw()
{
	//�e����ŏ��ɕ`��
	for (int i = 0; i < BOSS_SHOTNUM; ++i) {
		if (shot[i].flag) {
			DrawRotaGraph(shot[i].x, shot[i].y, 1.0, shot[i].rad + 90 * PI / 180, shot[i].gh, TRUE);
		}
	}

	//�e�����������Ƃ��̓_���[�W�p�̉摜��`��A
	if (damageflag) {
		DrawRotaGraph(x, y, 1.0, 0, gh_face[1], TRUE);
	}
	else {
		//���������Ƃ��͒ʏ�`��
		DrawRotaGraph(x, y, 1.0, 0, gh_face[0], TRUE);
	}


	damageflag = false;
}

bool BOSS::ShotOutCheck(int i)
{
	if (shot[i].x < -20 || shot[i].x>420 || shot[i].y < -20 || shot[i].y>500) {
		return true;
	}
	else {
		return false;
	}
}

bool BOSS::GetShotPosition(int index, double* x, double* y, int* type)
{
	if (shot[index].flag) {
		*x = shot[index].x;
		*y = shot[index].y;
		*type = shot[index].type;
		return true;
	}
	else {
		return false;
	}

}

bool BOSS::GetGrazeFlag(int index)
{
	return shot[index].gflag;
}

void BOSS::SetGrazeFlag(int index)
{
	shot[index].gflag = true;
}

void BOSS::SetDamageFlag()
{
	damageflag = true;
}

void BOSS::SetFlag(bool f)
{
	flag = f;
}

bool BOSS::GetFlag()
{
	return flag;
}

bool BOSS::GetShotSound()
{
	return s_shot;
}


void BOSS::GetPosition(double* x, double* y)
{
	*x = this->x;
	*y = this->y;
}


void BOSS::SetShotFlag(int index, bool flag)
{
	shot[index].flag = flag;
}

int BOSS::HpSet(int damage)
{
	prev_hp = hp;
	hp -= damage;

	return hp;
}

bool BOSS::GetNodamageFlag()
{
	return no_damage;
}


void BOSS::SetDamageSetting()
{

	prev_x = x;
	prev_y = y;

	movex = 200 - x;
	movey = 80 - y;

	angle = 0;

	no_damage = true;

	SetMovePattern(4);
	SetShotPattern(4);

}

int BOSS::GetPrevHp()
{
	return prev_hp;

}

void BOSS::SetMovePattern(int pattern)
{
	prev_move_pattern = move_pattern;
	move_pattern = pattern;
}

void BOSS::MoveToDefault()
{

	double temp;

	angle += 2;

	temp = sin(angle * PI / 180);

	x = prev_x + temp * movex;
	y = prev_y + temp * movey;

	if (angle == 90) {

		SetMovePattern(prev_move_pattern + 1);
		SetShotPattern(prev_shot_pattern + 1);
		no_damage = false;

		if (move_pattern == 3)
			MoveInit(200, 160, 2);
	}

}

void BOSS::SetShotPattern(int pattern)
{

	prev_shot_pattern = shot_pattern;
	shot_pattern = pattern;

}


void BOSS::All()
{
	Move();

	if (shotflag) {
		clock_t end = clock();
		if (40 < end - start) {
			Shot();
			start = end;
		}
	}

	Draw();

	++count;
}
