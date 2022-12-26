#include "title_ui.h"
#include "input.h"
#include "text.h"

//マクロ定義
#define TEXT_COLOR1 (XMFLOAT4(0.5f, 0.5f, 0.5f, 0.8f))	// 選択されていないときの色
#define TEXT_COLOR2 (XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f))	// 選択されている時の色

#define TEXT_SIZE1	(40)	// 選択されていないときのサイズ
#define TEXT_SIZE2	(50)	// 選択されている時のサイズ

#define TEXT_POS_X		(SCREEN_WIDTH / 2)	// テキストのXの座標
#define TEXT_POS_Y		(250)				// テキストのYの座標
#define TEXT_POS_Y_PLUS	(80)				// テキストのYの座標の差

enum MENUE {
	START,
	OPTION,
	EXIT,
	MENUE_MAX,
};


static TEXT g_textParameter[MENUE_MAX];
static int g_select;
static char g_text[MENUE_MAX][128] = {	{"ＳＴＡＲＴ"},
										{"ＯＰＴＩＯＮ"},
										{"ＥＸＩＴ"} };

HRESULT InitTitleUI(void) {

	for (int i = 0; i < MENUE_MAX; i++) {
		g_textParameter[i].color = TEXT_COLOR1;
		g_textParameter[i].size = TEXT_SIZE1;
		g_textParameter[i].pos = XMFLOAT2((float)TEXT_POS_X, (float)(TEXT_POS_Y + (i * TEXT_POS_Y_PLUS)));
	}

	g_select = 0;

	return S_OK;
}
void UninitTitleUI(void) {
}
void UpdateTitleUI(void) {

	// 選択されている物を変更する
	if (GetInputTrigger(MOVE_FRONT)) g_select--;
	if (GetInputTrigger(MOVE_BACK)) g_select++;

	g_select = (int)Clamp((float)g_select, 0.0, (float)MENUE_MAX-1);


	if (GetInputTrigger(MOVE_JUMP)) {
		switch (g_select)
		{
		case START:
			SetMode(MODE_GAME);
			break;
		case OPTION:
			
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

void DrawTitleUI(void) {

	//選択されている文字の色とサイズを変える。
	for (int i = 0; i < MENUE_MAX; i++) {
		g_textParameter[i].color = TEXT_COLOR1;
		g_textParameter[i].size = TEXT_SIZE1;
		g_textParameter[i].pos = XMFLOAT2((float)TEXT_POS_X, (float)(TEXT_POS_Y + (i * TEXT_POS_Y_PLUS)));
	}
	g_textParameter[g_select].color = TEXT_COLOR2;
	g_textParameter[g_select].size = TEXT_SIZE2;


	
	for (int i = 0; i < MENUE_MAX; i++) {
		SetText(g_textParameter[i], g_text[i]);
	}

}