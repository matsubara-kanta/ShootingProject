#include "pch.h"
#include "control.h"


//�L�[�擾�p�z��
char key[256];

int g_count;

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}


	CONTROL& control = CONTROL::GetInstance();
	int Time;

	while (ProcessMessage() == 0 && GetHitKeyStateAll(key) == 0) {
		Time = GetNowCount();
		ClearDrawScreen();
		control.All();
		ScreenFlip();
		while (GetNowCount() - Time < 17) {}


	}


	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}