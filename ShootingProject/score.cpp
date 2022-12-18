#include "score.h"
#include"pch.h"



SCORE::SCORE()
{
	LoadDivGraph("Picture/number.png", 10, 10, 1, 19, 27, g_number);

	font = CreateFontToHandle("ＭＳ ゴシック", 25, 9, DX_FONTTYPE_NORMAL);

	high_score = 0;

	score = 0;

	graze = 0;

	life = 0;

	power = PLAYER_PINIT;

	current_e_num = 0;
	total_e_num = 0;

}


void SCORE::SetScore(SCOREDATA data, int val)
{
	switch (data) {

	case HIGH_SCORE:
		high_score += val;
		break;

	case CURRENT_SCORE:
		score += val;
		break;

	case GRAZE_SCORE:
		graze += val;
		break;

	case LIFE_SCORE:
		life = val;
		break;

	case POWER_SCORE:
		power = val;
		break;

	case CURRENT_E_NUM:
		current_e_num += val;
		break;

	case TOTAL_E_NUM:
		total_e_num += val;
		break;
	}
}

int SCORE::GetScore(SCOREDATA data)
{

	switch (data) {

	case HIGH_SCORE:
		return high_score;
		break;

	case CURRENT_SCORE:
		return score;
		break;

	case GRAZE_SCORE:
		return graze;
		break;

	case LIFE_SCORE:
		return life;
		break;

	case POWER_SCORE:
		return power;
		break;

	case CURRENT_E_NUM:
		return current_e_num;
		break;

	case TOTAL_E_NUM:
		return total_e_num;
		break;
	}

	//該当しないときはー1を返す。
	return -1;

}

void SCORE::Draw()
{
	char buf[100];
	int num;
	//スコアボードの文字の描画
	int white = GetColor(255, 255, 255);
	DrawStringToHandle(SCORE_X, 10, "HIGH SCORE", white, font);
	DrawStringToHandle(SCORE_X, 70, "SCORE", white, font);
	DrawStringToHandle(SCORE_X, 140, "GRAZE", white, font);
	DrawStringToHandle(SCORE_X, 172, "LIFE", white, font);
	DrawStringToHandle(SCORE_X, 205, "POWER", white, font);
	DrawStringToHandle(SCORE_X, 235, "CURRENT", white, font);
	DrawStringToHandle(SCORE_X, 265, "ALL", white, font);

	//ハイスコア描画
	num = sprintf(buf, "%d", high_score);
	for (int i = 0; i < num; ++i) {
		DrawGraph(SCORE_X + 20 + i * 19, 35, g_number[(buf[i] - '0')], TRUE);
	}

	//スコア描画
	num = sprintf(buf, "%d", score);
	for (int i = 0; i < num; ++i) {
		DrawGraph(SCORE_X + 20 + i * 19, 95, g_number[(buf[i] - '0')], TRUE);
	}

	//グレイズ数描画
	num = sprintf(buf, "%d", graze);
	for (int i = 0; i < num; ++i) {
		DrawGraph(SCORE_X + 100 + i * 19, 145, g_number[(buf[i] - '0')], TRUE);
	}

	//ライフ数描画
	num = sprintf(buf, "%d", life);
	for (int i = 0; i < num; ++i) {
		DrawGraph(SCORE_X + 100 + i * 19, 175, g_number[(buf[i] - '0')], TRUE);
	}

	num = sprintf(buf, "%d", power);
	for (int i = 0; i < num; ++i) {
		DrawGraph(SCORE_X + 100 + i * 19, 205, g_number[(buf[i] - '0')], TRUE);
	}

	num = sprintf(buf, "%d", current_e_num);
	for (int i = 0; i < num; ++i) {
		DrawGraph(SCORE_X + 100 + i * 19, 235, g_number[(buf[i] - '0')], TRUE);
	}

	num = sprintf(buf, "%d", total_e_num);
	for (int i = 0; i < num; ++i) {
		DrawGraph(SCORE_X + 100 + i * 19, 265, g_number[(buf[i] - '0')], TRUE);
	}
}

void SCORE::All()
{
	Draw();
}

