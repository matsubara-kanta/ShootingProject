#pragma once
#include <windows.h>

//プレイヤーの歩くスピード
#define PLAYER_SPEED 4
// 余白
#define MARGIN 10
// 背景のスクロールスピード
#define SCROLL_SPEED 2
// 弾の最大数
#define PSHOT_NUM 50
#define PSHOT_SPEED 14
#define ENEMY_SNUM 50
#define ENEMY_NUM 50
#define PI 3.14

//当たり判定用半径定義
#define PLAYER_COLLISION 2
#define ENEMY1_COLLISION 14

#define PSHOT_COLLISION 3
#define ESHOT0_COLLISION 6
#define ESHOT1_COLLISION 3
#define ESHOT2_COLLISION 2

#define PLAYER_INITX 200
#define PLAYER_INITY 420

#define EFFECT_EDEADNUM 20
#define EFFECT_PDEADNUM 20

#define GRAZE_COLLISION 10
#define GRAZE_NUM 50

#define PLAYER_LIFE 5

//スコアの文字描画の基準となるX座標
#define SCORE_X 390

//アイテムの当たり判定用半径
#define ITEM_COLLISION 16
//アイテムの総数
#define ITEM_NUM 30

#define PLAYER_PINIT 8

#define BALL_SHAKE 15

#define BALL_INITX 50
#define BALL_INITY 30

struct SHOT {
	bool flag; // 弾が発射中かどうか
	double x;
	double y;
	int gh;
	int width, height;
	double rad;//角度
	int type;//弾の種類(0なら通常、1なら追跡弾)
};

struct E_SHOT {
	bool flag; // 弾が発射中かどうか
	double x;
	double y;
	double rad;
	int gh;
	int width, height;
	int pattern;
	int speed;
	bool gflag;//グレイズ判定用フラグ
};

struct ENEMYDATA {
	int type;//敵種類
	int stype;//弾種類
	int m_pattern;//移動パターン
	int s_pattern;//発射パターン
	int in_time;//出現時間
	int stop_time;//停止時間
	int shot_time;//弾発射時間
	int out_time;//帰還時間
	int x;//x座標
	int y;//y座標
	int speed;//弾スピード
	int hp;//HP
	int item;//アイテム
};

struct PEFFECT_EXPAND {
		double x, y;
		double rad;
		int speed;
};






//メッセージボックス
#define MSG(m) {\
	MessageBox(NULL,m,"メッセージ",MB_OK);}

//extern宣言してkey配列にどこからでもアクセスできるようにする
extern char key[256];
extern int g_count;