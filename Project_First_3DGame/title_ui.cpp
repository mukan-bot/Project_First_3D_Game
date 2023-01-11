//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "title_ui.h"
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

#define OPTION_TEXT_POS_X		(SCREEN_WIDTH / 2)	// テキストのXの座標
#define OPTION_TEXT_POS_Y		(100)				// テキストのYの座標
#define OPTION_TEXT_POS_Y_PLUS	(80)				// テキストのYの座標の差

#define TUTORIAL_TEXT_POS_X		(SCREEN_WIDTH / 2)	// テキストのXの座標
#define TUTORIAL_TEXT_POS_Y		(100)				// テキストのYの座標
#define TUTORIAL_TEXT_POS_Y_PLUS	(80)				// テキストのYの座標の差


enum MENUE {
	START,
	OPTION,
	TUTORIAL,
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

enum TUTORIAL {
	TUTORIAL_KEYBOARD,
	TUTORIAL_D_INPUT,
	TUTORIAL_X_INPUT,
	TUTORIAL_BACK,
	TUTORIAL_MAX,
};

static TEXT g_menueTextParameter[MENUE_MAX];
static int g_menueSelect;
static bool g_isOption;
static char g_menueText[MENUE_MAX][128] = {	{"ＳＴＡＲＴ"},
										{"ＯＰＴＩＯＮ"},
										{"ＴＵＴＯＲＩＡＬ"},
										{"ＥＸＩＴ"} 
};
static TEXT g_optionTextParameter[OPTION_MAX];
static int g_optionSelect;
static char g_optionText[OPTION_MAX][128] = { {"ＢＧＭ　ＶＯＬＵＭＥ"},
											{"ＳＥ　ＶＯＬＵＭＥ"},
											{"ＬＯＯＫ　ＳＥＮＳＩＴＩＶＥ"},
											{"ＢＡＣＫ"} };

static TEXT g_tutorialTextParameter[MENUE_MAX];
static int g_tutorialSelect;
static bool g_isTutorial;
static char g_tutorialText[TUTORIAL_MAX][128] = { {"キーボード"},
												{"ＤｉｒｅｃｔＩｎｐｕｔ"},
												{"ＸＩｎｐｕｔ"},
												{"ＢＡＣＫ"}
};

HRESULT InitTitleUI(void) {
	SetCursorMove(true);	//カーソルを動くようにしておく
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

	if (g_isOption) {
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
	else if (g_isTutorial) {
		// 選択されている物を変更する
		if (GetInputTrigger(MOVE_FRONT)) g_optionSelect--;
		if (GetInputTrigger(MOVE_BACK)) g_optionSelect++;

		g_tutorialSelect = (int)Clamp((float)g_optionSelect, 0.0, (float)OPTION_MAX - 1);

		// 選択の決定
		if (GetInputTrigger(MOVE_JUMP)) {
			switch (g_tutorialSelect)
			{
			case TUTORIAL_KEYBOARD:
				break;
			case TUTORIAL_D_INPUT:
				break;
			case TUTORIAL_X_INPUT:
				break;
			case TUTORIAL_BACK:
				g_isTutorial = false;
				break;
			case TUTORIAL_MAX:
				break;
			default:
				break;
			}
		}
	}
	else{
		// 選択されている物を変更する
		if (GetInputTrigger(MOVE_FRONT)) g_menueSelect--;
		if (GetInputTrigger(MOVE_BACK)) g_menueSelect++;

		g_menueSelect = (int)Clamp((float)g_menueSelect, 0.0, (float)MENUE_MAX - 1);

		// 選択の決定
		if (GetInputTrigger(MOVE_JUMP)) {
			switch (g_menueSelect)
			{
			case START:
				TEXT text;
				text.color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
				text.pos = XMFLOAT2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 130);
				text.size = 80;
				SetText(text, "ナウローディング");

				Clear();
				// 2Dの物を描画する処理
				// Z比較なし
				SetDepthEnable(false);
				// ライティングを無効
				SetLightEnable(false);

				Draw_text();

				// ライティングを有効に
				SetLightEnable(true);	//TODO:ライト作ったらtrueに変える
				// Z比較あり
				SetDepthEnable(true);
				Present();

				SetMode(MODE_GAME);
				break;
			case OPTION:
				g_optionSelect = 0;
				g_isOption = true;
				break;
			case TUTORIAL:
				g_isTutorial = true;
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

}

void DrawTitleUI(void) {
	if (g_isOption) {
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

	else if (g_isTutorial) {		//選択されている文字の色とサイズを変える。
		for (int i = 0; i < OPTION_MAX; i++) {
			g_tutorialTextParameter[i].color = TEXT_COLOR1;
			g_tutorialTextParameter[i].size = TEXT_SIZE1;
			g_tutorialTextParameter[i].pos = XMFLOAT2((float)OPTION_TEXT_POS_X, (float)(OPTION_TEXT_POS_Y + (i * OPTION_TEXT_POS_Y_PLUS)));
		}
		g_tutorialTextParameter[g_tutorialSelect].color = TEXT_COLOR2;
		g_tutorialTextParameter[g_tutorialSelect].size = TEXT_SIZE2;


		for (int i = 0; i < OPTION_MAX; i++) {
			SetText(g_tutorialTextParameter[i], g_tutorialText[i]);
		}
	}

	else {
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
		text.pos = XMFLOAT2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 130);
		text.size = 80;
		SetText(text, "ドクロをたおすゲーム");




	}

}