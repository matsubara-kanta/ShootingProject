#pragma once
#include <windows.h>

//プレイヤーの歩くスピード
#define PLAYER_SPEED 4
// 余白
#define MARGIN 10
// 背景のスクロールスピード
#define SCROLL_SPEED 2
// 弾の最大数
#define PSHOT_NUM 20
#define PSHOT_SPEED 14
#define ENEMY_SNUM 50
#define ENEMY_NUM 5
#define PI 3.1415926535897932384626433832795f

//当たり判定用半径定義
#define PLAYER_COLLISION 6
#define ENEMY1_COLLISION 14

#define PSHOT_COLLISION 3
#define ESHOT1_COLLISION 12
#define ESHOT2_COLLISION 3
#define ESHOT3_COLLISION 2



struct SHOT {
	bool flag; // 弾が発射中かどうか
	double x;
	double y;
	int gh;
	int width, height;
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


//メッセージボックス
#define MSG(m) {\
	MessageBox(NULL,m,"メッセージ",MB_OK);}

//extern宣言してkey配列にどこからでもアクセスできるようにする
extern char key[256];
extern int g_count;