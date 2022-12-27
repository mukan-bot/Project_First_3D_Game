#include "title_ui.h"
#include "input.h"
#include "text.h"

//マクロ定義
#define TEXT_COLOR1 (XMFLOAT4(0.5f, 0.5f, 0.5f, 0.8f))	// 選択されていないときの色
#define TEXT_COLOR2 (XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f))	// 選択されている時の色

#define TEXT_SIZE1	(40)	// 選択されていないときのサイズ
#define TEXT_SIZE2	(50)	// 選択されている時のサイズ

#define MENUE_TEXT_POS_X		(SCREEN_WIDTH / 2)	// テキストのXの座標
#define MENUE_TEXT_POS_Y		(250)				// テキストのYの座標
#define MENUE_TEXT_POS_Y_PLUS	(80)				// テキストのYの座標の差

#define OPTION_TEXT_POS_X		(SCREEN_WIDTH / 2)	// テキストのXの座標
#define OPTION_TEXT_POS_Y		(100)				// テキストのYの座標
#define OPTION_TEXT_POS_Y_PLUS	(80)				// テキストのYの座標の差

enum MENUE {
	START,
	OPTION,
	EXIT,
	MENUE_MAX,
};

enum OPTION_MENUE {
	BGM_VOLUME,
	SE_VOLUME,
	LOOK_SENSITIVE,
	BACK,
	OPTION_MAX,
};


static TEXT g_menueTextParameter[MENUE_MAX];
static int g_menueSelect;
static bool g_isOption;
static char g_menueText[MENUE_MAX][128] = {	{"ＳＴＡＲＴ"},
										{"ＯＰＴＩＯＮ"},
										{"ＥＸＩＴ"} 
};
static TEXT g_optionTextParameter[OPTION_MAX];
static int g_optionSelect;
static char g_optionText[OPTION_MAX][128] = { {"ＢＧＭ　ＶＯＬＵＭＥ"},{"ＳＥ　ＶＯＬＵＭＥ"},{"ＬＯＯＫ　ＳＥＮＳＩＴＩＶＥ"},{"ＢＡＣＫ"} };

HRESULT InitTitleUI(void) {

	for (int i = 0; i < MENUE_MAX; i++) {
		g_menueTextParameter[i].color = TEXT_COLOR1;
		g_menueTextParameter[i].size = TEXT_SIZE1;
		g_menueTextParameter[i].pos = XMFLOAT2((float)MENUE_TEXT_POS_X, (float)(MENUE_TEXT_POS_Y + (i * MENUE_TEXT_POS_Y_PLUS)));
	}
	g_menueSelect = 0;

	for (int i = 0; i < OPTION_MAX; i++) {
		g_optionTextParameter[i].color = TEXT_COLOR1;
		g_optionTextParameter[i].size = TEXT_SIZE1;
		g_optionTextParameter[i].pos = XMFLOAT2((float)OPTION_TEXT_POS_X, (float)(OPTION_TEXT_POS_Y + (i * OPTION_TEXT_POS_Y_PLUS)));
	}
	g_optionSelect = 0;

	return S_OK;
}
void UninitTitleUI(void) {
}
void UpdateTitleUI(void) {

	if (!g_isOption) {
		// 選択されている物を変更する
		if (GetInputTrigger(MOVE_FRONT)) g_menueSelect--;
		if (GetInputTrigger(MOVE_BACK)) g_menueSelect++;

		g_menueSelect = (int)Clamp((float)g_menueSelect, 0.0, (float)MENUE_MAX - 1);

		// 選択の決定
		if (GetInputTrigger(MOVE_JUMP)) {
			switch (g_menueSelect)
			{
			case START:
				SetMode(MODE_GAME);
				break;
			case OPTION:
				g_optionSelect = 0;
				g_isOption = true;
				break;
			case EXIT:
				PostQuitMessage(0);
				break;
			case MENUE_MAX:
				break;
			default:
				break;
			}
		}
	}

	else{
		// 選択されている物を変更する
		if (GetInputTrigger(MOVE_FRONT)) g_optionSelect--;
		if (GetInputTrigger(MOVE_BACK)) g_optionSelect++;

		g_optionSelect = (int)Clamp((float)g_optionSelect, 0.0, (float)OPTION_MAX - 1);

		// 選択の決定
		if (GetInputTrigger(MOVE_JUMP)) {
			switch (g_optionSelect)
			{
			case BGM_VOLUME:
				break;
			case SE_VOLUME:
				break;
			case LOOK_SENSITIVE:
				break;
			case BACK:
				g_isOption = false;
				break;
			case OPTION_MAX:
				break;
			default:
				break;
			}
		}
	}

}

void DrawTitleUI(void) {

	if (!g_isOption) {
		//選択されている文字の色とサイズを変える。
		for (int i = 0; i < MENUE_MAX; i++) {
			g_menueTextParameter[i].color = TEXT_COLOR1;
			g_menueTextParameter[i].size = TEXT_SIZE1;
			g_menueTextParameter[i].pos = XMFLOAT2((float)MENUE_TEXT_POS_X, (float)(MENUE_TEXT_POS_Y + (i * MENUE_TEXT_POS_Y_PLUS)));
		}
		g_menueTextParameter[g_menueSelect].color = TEXT_COLOR2;
		g_menueTextParameter[g_menueSelect].size = TEXT_SIZE2;


		for (int i = 0; i < MENUE_MAX; i++) {
			SetText(g_menueTextParameter[i], g_menueText[i]);
		}
	}

	else {
		//選択されている文字の色とサイズを変える。
		for (int i = 0; i < OPTION_MAX; i++) {
			g_optionTextParameter[i].color = TEXT_COLOR1;
			g_optionTextParameter[i].size = TEXT_SIZE1;
			g_optionTextParameter[i].pos = XMFLOAT2((float)OPTION_TEXT_POS_X, (float)(OPTION_TEXT_POS_Y + (i * OPTION_TEXT_POS_Y_PLUS)));
		}
		g_optionTextParameter[g_optionSelect].color = TEXT_COLOR2;
		g_optionTextParameter[g_optionSelect].size = TEXT_SIZE2;


		for (int i = 0; i < OPTION_MAX; i++) {
			SetText(g_optionTextParameter[i], g_optionText[i]);
		}
	}

}