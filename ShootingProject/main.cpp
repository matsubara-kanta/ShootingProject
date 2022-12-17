#include "pch.h"
#include "control.h"


//キー取得用配列
char key[256];

int g_count;

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
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


	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}