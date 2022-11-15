//#include "DxLib.h"
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//
//{
//
//	ChangeWindowMode(TRUE);
//
//	if (DxLib_Init() == -1) // ＤＸライブラリ初期化処理
//
//	{
//
//		return -1; // エラーが起きたら直ちに終了
//	}
//
//	int gh;
//
//	LoadGraphScreen(0, 0, "Picture/star.png", TRUE);
//
//	gh = LoadGraph("Picture/star.png");
//
//	DrawGraph(300, 0, gh, TRUE);
//
//	WaitKey(); // キー入力待ち
//
//	DxLib_End(); // ＤＸライブラリ使用の終了処理
//
//	return 0; // ソフトの終了
//}
