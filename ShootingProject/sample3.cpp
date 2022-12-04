#include "DxLib.h"
#include <cmath>

#define PI  3.1415926535897932384626433832795f


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)

{

	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1) // ＤＸライブラリ初期化処理

	{

		return -1; // エラーが起きたら直ちに終了
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
			//DrawString(300, 240, "←キーが押されています", 0xffff);
			x -= (int)4 * move;
		}
		if (key[KEY_INPUT_RIGHT] == 1) {
			//DrawString(300, 240, "↑キーが押されています", 0xffff);
			x += (int)4 * move;
		}

		//画面移動制御
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
		//	//DrawString(300, 240, "→キーが押されています", 0xffff);
		//	y -= (int)4 * move;
		//}
		//if (key[KEY_INPUT_DOWN] == 1) {
		//	//DrawString(300, 240, "↓キーが押されています", 0xffff);
		//	y += (int)4 * move;
		//}

			//左キーが押されてて、かつxcountが０以上なら０にしてから１引く。
			//それ以外は１引く
		if (key[KEY_INPUT_LEFT] == 1) {
			if (xcount > 0)
				xcount = 0;
			--xcount;
		}
		//右キーが押されてて、かつxcountが０以下なら０にしてから１足す。
		//それ以外は１引く
		if (key[KEY_INPUT_RIGHT] == 1) {
			if (xcount < 0)
				xcount = 0;
			++xcount;
		}
		//上キーが押されてて、かつycountが０以上なら０にしてから１引く。
		//それ以外は１引く
		if (key[KEY_INPUT_UP] == 1) {
			if (ycount > 0)
				ycount = 0;
			--ycount;
		}
		//下キーが押されてて、かつycountが０以下なら０にしてから１足す。
		//それ以外は１足す
		if (key[KEY_INPUT_DOWN] == 1) {
			if (ycount < 0)
				ycount = 0;
			++ycount;
		}

		//カウント数から添字を求める。
		ix = abs(xcount) % 30 / 10;
		iy = abs(ycount) % 30 / 10;
		//xカウントがプラスなら右向きなので2行目の先頭添字番号を足す。
		if (xcount > 0) {
			ix += 3;
			result = ix;
		}
		else if (xcount < 0) {
			//マイナスなら左向きなので、4行目の先頭添字番号を足す。
			ix += 9;
			result = ix;
		}

		//yカウントがプラスなら下向きなので、3行目の先頭添字番号を足す。
		if (ycount > 0) {
			iy += 6;
			result = iy;
		}
		else if (ycount < 0) {
			//１行目の先頭添字番号は０なので何もする必要なし。(分かりやすくするために書いときました)
			iy += 0;
			result = iy;
		}

		//斜め移動の場合は横顔を優先
		if (move == (1 / std::sqrt(2.0)))
			result = ix;

		//描画
		DrawGraph(x, y, gh[result], TRUE);


		//押されてなければカウントをゼロにする。
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


	DxLib_End(); // ＤＸライブラリ使用の終了処理

	return 0; // ソフトの終了
}
