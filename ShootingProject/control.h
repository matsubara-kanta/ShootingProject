#pragma once

#include "player.h"
#include "back.h"
#include "enemy.h"


class CONTROL{
private:
	//プレイヤークラスのポインタ
	PLAYER* player;

	BACK* back;

	ENEMY* enemy[ENEMY_NUM];
	
public:
	CONTROL();
	~CONTROL();
	void All();
};