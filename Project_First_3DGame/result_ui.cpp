//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

#include "result_ui.h"
#include "input.h"
#include "input_M.h"
#include "text.h"

//マクロ定義
#define TEXT_COLOR1 (XMFLOAT4(0.5f, 0.5f, 0.5f, 0.8f))	// 選択されていないときの色
#define TEXT_COLOR2 (XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f))	// 選択されている時の色

#define TEXT_SIZE1	(40)	// 選択されていないときのサイズ
#define TEXT_SIZE2	(50)	// 選択されている時のサイズ

#define MENUE_TEXT_POS_X		(SCREEN_WIDTH / 2)	// テキストのXの座標
#define MENUE_TEXT_POS_Y		(250)				// テキストのYの座標
#define MENUE_TEXT_POS_Y_PLUS	(80)				// テキストのYの座標の差


enum MENUE {
	BACK_TO_TITLE,
	RESTART,
	EXIT,
	MENUE_MAX,
};


static TEXT g_menueTextParameter[MENUE_MAX];
static int g_menueSelect;
//static bool g_isOption;
static char g_menueText[MENUE_MAX][128] = { {"ＢＡＣＫ ＴＯ ＴＩＴＬＥ"},
										{"ＲＥＳＴＡＲＴ"},
										{"ＥＸＩＴ"}
};

HRESULT InitResultUI(void) {
	SetCursorMove(true);	//カーソルを動くようにしておく
	for (int i = 0; i < MENUE_MAX; i++) {
		g_menueTextParameter[i].color = TEXT_COLOR1;
		g_menueTextParameter[i].size = TEXT_SIZE1;
		g_menueTextParameter[i].pos = XMFLOAT2((float)MENUE_TEXT_POS_X, (float)(MENUE_TEXT_POS_Y + (i * MENUE_TEXT_POS_Y_PLUS)));
	}
	g_menueSelect = 0;


	return S_OK;
}
void UninitResultUI(void) {
}
void UpdateResultUI(void) {

	// 選択されている物を変更する
	if (GetInputTrigger(MOVE_FRONT)) g_menueSelect--;
	if (GetInputTrigger(MOVE_BACK)) g_menueSelect++;

	g_menueSelect = (int)Clamp((float)g_menueSelect, 0.0, (float)MENUE_MAX - 1);

	// 選択の決定
	if (GetInputTrigger(MOVE_JUMP)) {
		switch (g_menueSelect)
		{
		case BACK_TO_TITLE:
			SetMode(MODE_TITLE);
			break;
		case RESTART:
			SetMode(MODE_GAME);
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

void DrawResultUI(void) {
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


	TEXT text;
	text.color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	text.size = 80;
	if (GetIsClear()) {
		text.pos = XMFLOAT2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 130);
		SetText(text, "ゲームクリアー");
	}
	else {
		text.pos = XMFLOAT2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 130);
		SetText(text, "ゲームオーバー");
	}
}