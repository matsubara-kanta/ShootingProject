#pragma once

class PLAYER{
private:
	//x座標,y座標
	double x,y;

	//画像幅
	int width,height;

	//グラフィックハンドル格納用配列
	int gh[12];


	//移動係数
	float move;

	//横方向と縦方向のカウント数。
	int xcount,ycount;
	//添字用変数
	int ix,iy,result;
	//生きてるかどうかのフラグ
	bool life;

	SHOT shot[PSHOT_NUM];

	int count;
private:
	void Move();
	void Draw();
	void Shot();


public:
	PLAYER();
	void All();

};