#include <span>

#include "pch.h"
#include "player.h"


PLAYER::PLAYER()
{
	//�摜�ǂݍ���

	if (-1 == LoadDivGraph("Picture/charall.png", 12, 3, 4, 49, 66, gh)) {
		MSG("�G���[����");
	}

	width = 49;
	height = 66;


	//�ړ��W��
	move = 1.0f;

	//�������Əc�����̃J�E���g���B
	xcount = 0, ycount = 0;
	//�Y���p�ϐ�
	ix = 0, iy = 0, result = 0;

	//�����ʒu
	x = 180;
	y = 400;

	life = true;

	memset(shot, 0, sizeof(shot));

	//�e�摜�ǂݍ���
	int temp = LoadGraph("Picture/shot.png");
	int w, h;
	GetGraphSize(temp, &w, &h);

	for (int i = 0; i < PSHOT_NUM; ++i) {
		shot[i].flag = false;
		shot[i].gh = temp;
		shot[i].width = w;
		shot[i].height = h;
	}

	count = 0;


}
void PLAYER::Move()
{

	if (key[KEY_INPUT_LEFT] == 1 || key[KEY_INPUT_RIGHT] == 1) {

		if (key[KEY_INPUT_UP] == 1 || key[KEY_INPUT_DOWN] == 1) {
			//�ړ��W����O�D�V�P�ɐݒ�
			move = 0.71f;
		}
		else {
			//�΂߂���Ȃ���΂P�D�O�ɐݒ�
			move = 1.0f;
		}
	}
	else if (key[KEY_INPUT_UP] == 1 || key[KEY_INPUT_DOWN] == 1) {
		move = 1.0f;
	}


	if (key[KEY_INPUT_LEFT] == 1) {
		x -= (int)PLAYER_SPEED * move;
	}
	if (key[KEY_INPUT_RIGHT] == 1) {
		x += (int)PLAYER_SPEED * move;

	}
	if (key[KEY_INPUT_UP] == 1) {
		y -= (int)PLAYER_SPEED * move;

	}
	if (key[KEY_INPUT_DOWN] == 1) {
		y += (int)PLAYER_SPEED * move;

	}

	//<span class = "stress" >
		//�L�����̈ړ�����
	if (x > 400 - MARGIN) {
		x = 400 - MARGIN;
	}
	else if (x < MARGIN) {
		x = MARGIN;
	}

	if (y > 480 - height / 2 - MARGIN) {
		y = 480 - height / 2 - MARGIN;
	}
	else if (y < height / 2 + MARGIN) {
		y = height / 2 + MARGIN;
	}
	//< / span>


		//���L�[��������ĂāA����xcount���O�ȏ�Ȃ�O�ɂ��Ă���P�����B
		//����ȊO�͂P����
	if (key[KEY_INPUT_LEFT] == 1) {
		if (xcount > 0)
			xcount = 0;
		--xcount;

	}
	//�E�L�[��������ĂāA����xcount���O�ȉ��Ȃ�O�ɂ��Ă���P�����B
	//����ȊO�͂P����
	if (key[KEY_INPUT_RIGHT] == 1) {
		if (xcount < 0)
			xcount = 0;
		++xcount;
	}
	//��L�[��������ĂāA����ycount���O�ȏ�Ȃ�O�ɂ��Ă���P�����B
	//����ȊO�͂P����
	if (key[KEY_INPUT_UP] == 1) {
		if (ycount > 0)
			ycount = 0;
		--ycount;
	}
	//���L�[��������ĂāA����ycount���O�ȉ��Ȃ�O�ɂ��Ă���P�����B
	//����ȊO�͂P����
	if (key[KEY_INPUT_DOWN] == 1) {
		if (ycount < 0)
			ycount = 0;
		++ycount;
	}


	//�J�E���g������Y������߂�B
	ix = abs(xcount) % 30 / 10;
	iy = abs(ycount) % 30 / 10;

	//x�J�E���g���v���X�Ȃ�E�����Ȃ̂�2�s�ڂ̐擪�Y���ԍ��𑫂��B
	if (xcount > 0) {
		ix += 3;
		result = ix;
	}
	else if (xcount < 0) {
		//�}�C�i�X�Ȃ獶�����Ȃ̂ŁA4�s�ڂ̐擪�Y���ԍ��𑫂��B
		ix += 9;
		result = ix;
	}

	//y�J�E���g���v���X�Ȃ牺�����Ȃ̂ŁA3�s�ڂ̐擪�Y���ԍ��𑫂��B
	if (ycount > 0) {
		iy += 6;
		result = iy;
	}
	else if (ycount < 0) {
		//�P�s�ڂ̐擪�Y���ԍ��͂O�Ȃ̂ŉ������K�v�Ȃ��B(������₷�����邽�߂ɏ����Ƃ��܂���)
		iy += 0;
		result = iy;
	}

	//�΂߈ړ��̏ꍇ�͉����D��
	if (move == 0.71f)
		result = ix;


	//������ĂȂ���΃J�E���g��[���ɂ���B
	if (key[KEY_INPUT_LEFT] != 1 && key[KEY_INPUT_RIGHT] != 1) {
		xcount = 0;
	}
	if (key[KEY_INPUT_UP] != 1 && key[KEY_INPUT_DOWN] != 1) {
		ycount = 0;
	}

}

void PLAYER::Draw()
{
	//�e�`��
		for (int i = 0; i < PSHOT_NUM; ++i) {
				if (shot[i].flag) {
						DrawGraph(shot[i].x - shot[i].width / 2, shot[i].y - shot[i].height / 2, shot[i].gh, TRUE);
				}
		}

	//�����Ă�Ε`��
	if (life) {
		//�`��
		DrawGraph(x - width / 2, y - height / 2, gh[result], TRUE);
	}
}

void PLAYER::Shot() {
	//�L�[��������ĂĂ��A6���[�v�Ɉ�񔭎�
	if (key[KEY_INPUT_SPACE] == 1 && count % 6 == 0) {
		for (int i = 0; i < PSHOT_NUM; ++i) {
			if (shot[i].flag == false) {
				shot[i].flag = true;
				shot[i].x = x;
				shot[i].y = y;
				break;
			}
		}
	}

	//�e��ړ������鏈��
	for (int i = 0; i < PSHOT_NUM; ++i) {
		//���˂��Ă�e����
		if (shot[i].flag) {
			shot[i].y -= PSHOT_SPEED;

			//��ʂ̊O�ɂ͂ݏo������t���O��߂�
			if (shot[i].y < -10) {
				shot[i].flag = false;
			}
		}
	}


}


void PLAYER::All()
{
	Move();
	Shot();
	Draw();

	++count;
}