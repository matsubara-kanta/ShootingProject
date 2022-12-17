#include "item.h"
#include "pch.h"

int ITEM::gh[2];
int ITEM::ghs[2];

ITEM::ITEM()
{
	if (gh[0] == 0) {
		gh[0] = LoadGraph("Picture/item1.png");
		gh[1] = LoadGraph("Picture/item2.png");
		ghs[0] = LoadGraph("Picture/items1.png");
		ghs[1] = LoadGraph("Picture/items2.png");

	}
	x = y = 0;

	rad = 0;

	count = 0;

	fall_flag = false;

	flag = false;

}

void ITEM::Move()
{

	double tempy;

	//0.04���W�A��(��2�x)����]������B
	rad = 0.04 * count;

	++count;

	if (!fall_flag) {
		tempy = y;
		y += (y - prev_y) + 1;
		//���_�܂ł�������t���O���Ă�
		if ((y - prev_y) + 1 == 0) {
			fall_flag = true;
		}
		prev_y = tempy;
	}
	else {
		//�������͈�葬�x�ŗ���
		y += 1.5;
	}

	//��ʂ̊O�ɂ͂ݏo����t���O��߂��B
	if (y > 500) {
		Delete();
	}
}

void ITEM::Delete()
{
	count = 0;
	fall_flag = false;
	flag = false;
}

void ITEM::Draw()
{
	if (type > 1 || type < 0) {
	 	printf("error");
	}

    DrawRotaGraph(x, y, 1.0, rad, gh[type], TRUE);
	DrawRotaGraph(x, y, 1.0, 0, ghs[type], TRUE);
}

void ITEM::SetFlag(double x, double y, int type)
{
	this->x = x;
	this->y = y - 8;
	prev_y = y;
	this->type = type;

	flag = true;
}

bool ITEM::GetFlag()
{
	return flag;
}

void ITEM::GetPosition(double* x, double* y)
{
	*x = this->x;
	*y = this->y;
}

int ITEM::GetType()
{
	return type;
}

void ITEM::All()
{
	Move();
	Draw();
}
