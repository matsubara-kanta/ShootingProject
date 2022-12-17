#pragma once

enum SCOREDATA {
	HIGH_SCORE,
	CURRENT_SCORE,
	GRAZE_SCORE,
	LIFE_SCORE,
	POWER_SCORE,
	CURRENT_E_NUM,
	TOTAL_E_NUM
};

class SCORE {
private:
	//グラフィックハンドル
	int g_board[5], g_number[10];
	int font;

	int high_score, score, graze, life, power,current_e_num,total_e_num;

private:
	void Draw();
public:
	void SetScore(SCOREDATA data, int val);
	int GetScore(SCOREDATA data);
	void All();
	SCORE();
};
