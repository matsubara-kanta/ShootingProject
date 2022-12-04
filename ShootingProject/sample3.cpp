#include "DxLib.h"
#include <cmath>

#define PI  3.1415926535897932384626433832795f


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)

{

	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1) // �c�w���C�u��������������

	{

		return -1; // �G���[���N�����璼���ɏI��
	}

	int gh[12];
	char key[256];
	int x = 300, y = 360, y_prev = 0, y_temp = 0;

	LoadDivGraph("Picture/charall.png", 12, 3, 4, 49, 66, gh);

	int sh;
	sh = LoadSoundMem("SE/Bomb.mp3");

	float move = 1.0f;

	int dx = 0;
	int dy = 0;

	int xcount = 0, ycount = 0;
	int ix = 0, iy = 0, result = 0;

	bool jflag = false;





	SetDrawScreen(DX_SCREEN_BACK);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0)
	{

		if (key[KEY_INPUT_LEFT] == 1 || key[KEY_INPUT_RIGHT] == 1) {
			if (key[KEY_INPUT_UP] == 1 || key[KEY_INPUT_DOWN] == 1) {
				move = 1 / std::sqrt(2.0);
			}
			else {
				move = 1.0f;
			}
		}
		else if (key[KEY_INPUT_UP] == 1 || key[KEY_INPUT_DOWN] == 1) {
			move = 1.0f;
		}


		if (key[KEY_INPUT_LEFT] == 1) {
			//DrawString(300, 240, "���L�[��������Ă��܂�", 0xffff);
			x -= (int)4 * move;
		}
		if (key[KEY_INPUT_RIGHT] == 1) {
			//DrawString(300, 240, "���L�[��������Ă��܂�", 0xffff);
			x += (int)4 * move;
		}

		//��ʈړ�����
		if (x + (49 / 2) > 640)
			x = 640 - (49 / 2);
		if (x < (49 / 2))
			x = (49 / 2);


		if (jflag == true) {
			y_temp = y;
			y += (y - y_prev) + 1;
			y_prev = y_temp;
			if (y == 360)
				jflag = false;
		}

		if (key[KEY_INPUT_SPACE] == 1 && jflag == false) {
			jflag = true;
			y_prev = y;
			y = y - 20;
		}

		//if (key[KEY_INPUT_UP] == 1) {
		//	//DrawString(300, 240, "���L�[��������Ă��܂�", 0xffff);
		//	y -= (int)4 * move;
		//}
		//if (key[KEY_INPUT_DOWN] == 1) {
		//	//DrawString(300, 240, "���L�[��������Ă��܂�", 0xffff);
		//	y += (int)4 * move;
		//}

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

		//�J�E���g������Y�������߂�B
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
			//�P�s�ڂ̐擪�Y���ԍ��͂O�Ȃ̂ŉ�������K�v�Ȃ��B(������₷�����邽�߂ɏ����Ƃ��܂���)
			iy += 0;
			result = iy;
		}

		//�΂߈ړ��̏ꍇ�͉����D��
		if (move == (1 / std::sqrt(2.0)))
			result = ix;

		//�`��
		DrawGraph(x, y, gh[result], TRUE);


		//������ĂȂ���΃J�E���g���[���ɂ���B
		if (key[KEY_INPUT_LEFT] != 1 && key[KEY_INPUT_RIGHT] != 1) {
			xcount = 0;
		}
		if (key[KEY_INPUT_UP] != 1 && key[KEY_INPUT_DOWN] != 1) {
			ycount = 0;
		}


		if (key[KEY_INPUT_ESCAPE] == 1) {
			break;
		}
		if (key[KEY_INPUT_RETURN] == 1) {
			if (CheckSoundMem(sh) == 0)
				PlaySoundMem(sh, DX_PLAYTYPE_BACK, TRUE);
		}
		if (key[KEY_INPUT_SPACE] == 1) {
			StopSoundMem(sh);
		}


		//x += 2;
		//if (x == 640)
		//	break;

	}

	//WaitKey();
	DeleteSoundMem(sh);


	DxLib_End(); // �c�w���C�u�����g�p�̏I������

	return 0; // �\�t�g�̏I��
}
