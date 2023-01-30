//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "title_ui.h"
#include "input.h"
#include "input_M.h"
#include "text.h"
#include "sound.h"
#include "title_bg.h"	//ロード画面で表示するため

//マクロ定義
#define TEXT_COLOR1 (XMFLOAT4(0.5f, 0.5f, 0.5f, 0.8f))	// 選択されていないときの色
#define TEXT_COLOR2 (XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f))	// 選択されている時の色

#define TEXT_SIZE1	(40)	// 選択されていないときのサイズ
#define TEXT_SIZE2	(50)	// 選択されている時のサイズ

#define MENUE_TEXT_POS_X		(SCREEN_WIDTH / 2)	// テキストのXの座標
#define MENUE_TEXT_POS_Y		(250)				// テキストのYの座標
#define MENUE_TEXT_POS_Y_PLUS	(80)				// テキストのYの座標の差

#define OPTION_TEXT_POS_X		(SCREEN_WIDTH / 2)	// テキストのXの座標
#define OPTION_TEXT_POS_Y		(50)				// テキストのYの座標
#define OPTION_TEXT_POS_Y_PLUS	(60)				// テキストのYの座標の差

#define TUTORIAL_TEXT_POS_X		(SCREEN_WIDTH / 2)	// テキストのXの座標
#define TUTORIAL_TEXT_POS_Y		(50)				// テキストのYの座標
#define TUTORIAL_TEXT_POS_Y_PLUS	(30)				// テキストのYの座標の差
#define TUTORIAL_TEXT_SIZE1	(20)	// 選択されていないときのサイズ
#define TUTORIAL_TEXT_SIZE2	(30)	// 選択されている時のサイズ

#define TUTORIAL_TEXT_MAIN	(5)
#define TUTORIAL_TEXT_MAIN_POS_X		(SCREEN_WIDTH / 2)	// テキストのXの座標
#define TUTORIAL_TEXT_MAIN_POS_Y		(200)				// テキストのYの座標
#define TUTORIAL_TEXT_MAIN_POS_Y_PLUS	(70)				// テキストのYの座標の差
#define TUTORIAL_TEXT_MAIN_SIZE1		(40)	// 選択されていないときのサイズ
#define TUTORIAL_TEXT_MAIN_SIZE2		(50)	// 選択されている時のサイズ

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
	TUTORIAL_KEYBOARD = 0,
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
										{"ＭＡＮＵＡＬ"},
										{"ＥＸＩＴ"} 
};
static TEXT g_optionTextParameter[OPTION_MAX];
static int g_optionSelect;
static char g_optionText[OPTION_MAX][128] = { {"ＢＧＭ　ＶＯＬＵＭＥ"},
											{"ＳＥ　ＶＯＬＵＭＥ"},
											{"ＬＯＯＫ　ＳＥＮＳＩＴＩＶＩＴＹ"},
											{"ＢＡＣＫ"} };

static TEXT g_tutorialTextParameter[MENUE_MAX];
static int g_tutorialSelect;
static bool g_isTutorial;
static char g_tutorialText[TUTORIAL_MAX][128] = { {"キーボード"},
												{"ＤｉｒｅｃｔＩｎｐｕｔ"},
												{"ＸＩｎｐｕｔ"},
												{"ＢＡＣＫ"}
};

//optionのサウンドボリュームで使うやつ
float g_temp_bgm_vol;
float g_temp_se_vol;
float g_temp_sensitive;

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

	//ボリュームの初期値
	g_temp_bgm_vol = 0.1f;
	g_temp_se_vol = 0.1f;
	
	Sound_BGM_Volume(g_temp_bgm_vol);
	Sound_SE_Volume(g_temp_se_vol);

	g_temp_sensitive = 0.00003f;
	SetInputSensitive(g_temp_sensitive);

	return S_OK;
}
void UninitTitleUI(void) {
}
void UpdateTitleUI(void) {

	if (g_isOption) {// optionが選択されたらここ
		int temp = g_optionSelect;
		// 選択されている物を変更する
		if (GetInputTrigger(MOVE_FRONT)) g_optionSelect--;
		if (GetInputTrigger(MOVE_BACK)) g_optionSelect++;

		g_optionSelect = (int)Clamp((float)g_optionSelect, 0.0, (float)OPTION_MAX - 1);

		if (g_optionSelect != temp)PlaySound(SOUND_LABEL_SE_select1);

		// optionの何が選択されているか
		switch (g_optionSelect)
		{
		case BGM_VOLUME:

			if (GetInputPress(MOVE_JUMP)) {	// JUMPキーが押されていたら１０倍の値の増減
				if (GetInputTrigger(MOVE_LEFT)) {
					PlaySound(SOUND_LABEL_SE_select2);
					g_temp_bgm_vol -= 0.10f;
					g_temp_bgm_vol = Clamp(g_temp_bgm_vol, 0.0f, 1.0f);	// 値を一定の間に留める
					Sound_BGM_Volume(g_temp_bgm_vol);
				}
				if (GetInputTrigger(MOVE_RIGHT)) {
					PlaySound(SOUND_LABEL_SE_select2);
					g_temp_bgm_vol += 0.10f;
					g_temp_bgm_vol = Clamp(g_temp_bgm_vol, 0.0f, 1.0f);	// 値を一定の間に留める
					Sound_BGM_Volume(g_temp_bgm_vol);
				}
			}
			else {
				if (GetInputTrigger(MOVE_LEFT)) {
					PlaySound(SOUND_LABEL_SE_select2);
					g_temp_bgm_vol -= 0.01f;
					g_temp_bgm_vol = Clamp(g_temp_bgm_vol, 0.0f, 1.0f);	// 値を一定の間に留める
					Sound_BGM_Volume(g_temp_bgm_vol);
				}
				if (GetInputTrigger(MOVE_RIGHT)) {
					PlaySound(SOUND_LABEL_SE_select2);
					g_temp_bgm_vol += 0.01f;
					g_temp_bgm_vol = Clamp(g_temp_bgm_vol, 0.0f, 1.0f);	// 値を一定の間に留める
					Sound_BGM_Volume(g_temp_bgm_vol);
				}
			}
			break;
		case SE_VOLUME:
			if (GetInputPress(MOVE_JUMP)) {// JUMPキーが押されていたら１０倍の値の増減
				if (GetInputTrigger(MOVE_LEFT)) {
					PlaySound(SOUND_LABEL_SE_select2);
					g_temp_se_vol -= 0.10f;
					g_temp_se_vol = Clamp(g_temp_se_vol, 0.0f, 1.0f);	// 値を一定の間に留める
					Sound_SE_Volume(g_temp_se_vol);
				}
				if (GetInputTrigger(MOVE_RIGHT)) {
					PlaySound(SOUND_LABEL_SE_select2);
					g_temp_se_vol += 0.10f;
					g_temp_se_vol = Clamp(g_temp_se_vol, 0.0f, 1.0f);	// 値を一定の間に留める
					Sound_SE_Volume(g_temp_se_vol);
				}
			}
			else {
				if (GetInputTrigger(MOVE_LEFT)) {
					PlaySound(SOUND_LABEL_SE_select2);
					g_temp_se_vol -= 0.01f;
					g_temp_se_vol = Clamp(g_temp_se_vol, 0.0f, 1.0f);	// 値を一定の間に留める
					Sound_SE_Volume(g_temp_se_vol);
				}
				if (GetInputTrigger(MOVE_RIGHT)) {
					PlaySound(SOUND_LABEL_SE_select2);
					g_temp_se_vol += 0.01f;
					g_temp_se_vol = Clamp(g_temp_se_vol, 0.0f, 1.0f);	// 値を一定の間に留める
					Sound_SE_Volume(g_temp_se_vol);
				}
			}
			break;
		case LOOK_SENSITIVE:
			if (GetInputPress(MOVE_JUMP)) {// JUMPキーが押されていたら１０倍の値の増減
				if (GetInputTrigger(MOVE_LEFT)) {
					PlaySound(SOUND_LABEL_SE_select2);
					g_temp_sensitive -= 0.000001f;
					g_temp_sensitive = Clamp(g_temp_sensitive * 10000000, 0.0f, 1000.0f);	// 値を一定の間に留める
					g_temp_sensitive /= 10000000.0f;
					SetInputSensitive(g_temp_sensitive);
				}
				if (GetInputTrigger(MOVE_RIGHT)) {
					PlaySound(SOUND_LABEL_SE_select2);
					g_temp_sensitive += 0.000001f;
					g_temp_sensitive = Clamp(g_temp_sensitive * 10000000, 0.0f, 1000.0f);	// 値を一定の間に留める
					g_temp_sensitive /= 10000000.0f;
					SetInputSensitive(g_temp_sensitive);
				}
			}
			else {
				if (GetInputTrigger(MOVE_LEFT)) {
					PlaySound(SOUND_LABEL_SE_select2);
					g_temp_sensitive -= 0.0000001f;
					g_temp_sensitive = Clamp(g_temp_sensitive * 10000000, 0.0f, 1000.0f);	// 値を一定の間に留める
					g_temp_sensitive /= 10000000.0f;
					SetInputSensitive(g_temp_sensitive);
				}
				if (GetInputTrigger(MOVE_RIGHT)) {
					PlaySound(SOUND_LABEL_SE_select2);
					g_temp_sensitive += 0.0000001f;
					g_temp_sensitive = Clamp(g_temp_sensitive * 10000000, 0.0f, 1000.0f);	// 値を一定の間に留める
					g_temp_sensitive /= 10000000.0f;
					SetInputSensitive(g_temp_sensitive);
				}
			}
			break;
		case BACK:
			if (GetInputTrigger(MOVE_JUMP)) {
				g_isOption = false;	// optionが選択されていない状態に戻す（一番上）
			}
			break;
		case OPTION_MAX:
			break;
		default:
			break;
		}

	}

	else if (g_isTutorial) { // チュートリアルが選択されたらここ
		int temp = g_tutorialSelect;
		// 選択されている物を変更する
		if (GetInputTrigger(MOVE_FRONT)) g_tutorialSelect--;
		if (GetInputTrigger(MOVE_BACK)) g_tutorialSelect++;

		g_tutorialSelect = (int)Clamp((float)g_tutorialSelect, 0.0, (float)TUTORIAL_MAX - 1);

		if (g_tutorialSelect != temp)PlaySound(SOUND_LABEL_SE_select1);

		// 選択の決定
		if (GetInputTrigger(MOVE_JUMP)) {
			PlaySound(SOUND_LABEL_SE_select2);
			switch (g_tutorialSelect)
			{
			case TUTORIAL_KEYBOARD:
				break;
			case TUTORIAL_D_INPUT:
				break;
			case TUTORIAL_X_INPUT:
				break;
			case TUTORIAL_BACK:// チュートリアルが選択されていない状態に戻す（一番上）
				g_isTutorial = false;
				break;
			case TUTORIAL_MAX:
				break;
			default:
				break;
			}
		}
	}
	else{	// 何も選択されていない場合ここ
		int temp = g_menueSelect;

		// 選択されている物を変更する
		if (GetInputTrigger(MOVE_FRONT)) g_menueSelect--;
		if (GetInputTrigger(MOVE_BACK)) g_menueSelect++;

		g_menueSelect = (int)Clamp((float)g_menueSelect, 0.0, (float)MENUE_MAX - 1);


		if (g_menueSelect != temp)PlaySound(SOUND_LABEL_SE_select1);

		// 選択の決定
		if (GetInputTrigger(MOVE_JUMP)) {
			PlaySound(SOUND_LABEL_SE_select2);
			switch (g_menueSelect)
			{
			case START:
				//ロード画面を表示
				TEXT text;
				text.color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
				text.pos = XMFLOAT2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 130);
				text.size = 80;
				SetText(text, "ナウローディング");
				Clear();

				// ライティングを無効
				SetLightEnable(false);

				DrawTitleBG();

				// 2Dの物を描画する処理
				// Z比較なし
				SetDepthEnable(false);




				Draw_text();

				// ライティングを有効に
				SetLightEnable(true);	//TODO:ライト作ったらtrueに変える
				// Z比較あり
				SetDepthEnable(true);
				Present();


				//ロード画面のままゲームモード移行する
				SetMode(MODE_GAME);
				break;
			case OPTION: // optionが選択されているところで決定されたらoptionモードに移行
				g_optionSelect = 0;	// オプションの一番上が選択されている状態にする（Back連打しないように）
				g_isOption = true;
				break;
			case TUTORIAL: //tutorialが選択されているところで決定されたらtutorialモードに移行 
				g_tutorialSelect = 0; // チュートリアルの一番上が選択されている状態にする（Back連打しないように）
				g_isTutorial = true;
				break;
			case EXIT: // ゲームを終了する
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
	//タイトル画面（設定）
	if (g_isOption) {

		XMFLOAT2 pos = XMFLOAT2(OPTION_TEXT_POS_X, OPTION_TEXT_POS_Y);

		//選択されている文字の色とサイズを変える。
		for (int i = 0; i < OPTION_MAX; i++) {
			//選択されている物の色と大きさを変える
			if (g_optionSelect == i) {
				g_optionTextParameter[g_optionSelect].color = TEXT_COLOR2;
				g_optionTextParameter[g_optionSelect].size = TEXT_SIZE2;
			}
			else {
				g_optionTextParameter[i].color = TEXT_COLOR1;
				g_optionTextParameter[i].size = TEXT_SIZE1;
			}
			//場所を決める
			pos.x += 0.0f;
			pos.y += OPTION_TEXT_POS_Y_PLUS;
			g_optionTextParameter[i].pos = pos;

			SetText(g_optionTextParameter[i], g_optionText[i]);
			//場所を決める
			pos.x += 0.0f;
			pos.y += OPTION_TEXT_POS_Y_PLUS;
			g_optionTextParameter[i].pos = pos;
			switch (i)
			{
			case(BGM_VOLUME):
				SetText_d(g_optionTextParameter[i], g_temp_bgm_vol * 100);
				break;
			case(SE_VOLUME):
				SetText_d(g_optionTextParameter[i], g_temp_se_vol * 100);
				break;
			case(LOOK_SENSITIVE):
				SetText_d(g_optionTextParameter[i], GetInputSensitive() * 10000000);
				break;
			default:
				break;
			}
			

		}
	}

	//タイトル画面（チュートリアル）
	else if (g_isTutorial) {		//選択されている文字の色とサイズを変える。
		for (int i = 0; i < TUTORIAL_MAX; i++) {
			g_tutorialTextParameter[i].color = TEXT_COLOR1;
			g_tutorialTextParameter[i].size = TUTORIAL_TEXT_SIZE1;
			g_tutorialTextParameter[i].pos = XMFLOAT2((float)TUTORIAL_TEXT_POS_X, (float)(TUTORIAL_TEXT_POS_Y + (i * TUTORIAL_TEXT_POS_Y_PLUS)));
		}
		g_tutorialTextParameter[g_tutorialSelect].color = TEXT_COLOR2;
		g_tutorialTextParameter[g_tutorialSelect].size = TUTORIAL_TEXT_SIZE2;

		for (int i = 0; i < TUTORIAL_MAX; i++) {
			SetText(g_tutorialTextParameter[i], g_tutorialText[i]);
		}

		// それぞれ表示する
		switch (g_tutorialSelect)
		{
		case KEYBOARD:
		{
			TEXT tutorialTextMainP[TUTORIAL_TEXT_MAIN];
			char tutorialTextMain[TUTORIAL_TEXT_MAIN][128] = {
				{"いどう…ＷＡＳＤ"},
				{"ダッシュ…ＳＨＩＦＴ"},
				{"してん…やじるしキーｏｒマウス"},
				{"こうげき…１ｏｒＬクリック"},
				{"レティクル…ＱｏｒＲクリック"},
			};
			for (int i = 0; i < TUTORIAL_TEXT_MAIN; i++) {
				tutorialTextMainP[i].pos = XMFLOAT2((float)TUTORIAL_TEXT_MAIN_POS_X, (float)(TUTORIAL_TEXT_MAIN_POS_Y + (i * TUTORIAL_TEXT_MAIN_POS_Y_PLUS)));
				tutorialTextMainP[i].color = TEXT_COLOR2;
				tutorialTextMainP[i].size = TUTORIAL_TEXT_MAIN_SIZE1;
				SetText(tutorialTextMainP[i], tutorialTextMain[i]);


			}
			break;
		}
		case XBOX:
		{
			TEXT tutorialTextMainP[TUTORIAL_TEXT_MAIN];
			char tutorialTextMain[TUTORIAL_TEXT_MAIN][128] = {
				{"いどう…Ｌスティック"},
				{"ダッシュ…Ｌ３ボタン"},
				{"してん…Ｒスティック"},
				{"こうげき…ＬＢボタン"},
				{"レティクル…ＲＢボタン"},
			};
			for (int i = 0; i < TUTORIAL_TEXT_MAIN; i++) {
				tutorialTextMainP[i].color = TEXT_COLOR2;
				tutorialTextMainP[i].size = TUTORIAL_TEXT_MAIN_SIZE1;
				tutorialTextMainP[i].pos = XMFLOAT2((float)TUTORIAL_TEXT_MAIN_POS_X, (float)(TUTORIAL_TEXT_MAIN_POS_Y + (i * TUTORIAL_TEXT_MAIN_POS_Y_PLUS)));
				SetText(tutorialTextMainP[i], tutorialTextMain[i]);
			}
			break;
		}
		case PS:
		{
			TEXT tutorialTextMainP[TUTORIAL_TEXT_MAIN];
			char tutorialTextMain[TUTORIAL_TEXT_MAIN][128] = {
				{"いどう…Ｌスティック"},
				{"ダッシュ…Ｙボタン"},
				{"してん…Ｒスティック"},
				{"こうげき…Ｌ１ボタン"},
				{"レティクル…Ｒ１ボタン"},
			};
			for (int i = 0; i < TUTORIAL_TEXT_MAIN; i++) {
				tutorialTextMainP[i].color = TEXT_COLOR2;
				tutorialTextMainP[i].size = TUTORIAL_TEXT_MAIN_SIZE1;
				tutorialTextMainP[i].pos = XMFLOAT2((float)TUTORIAL_TEXT_MAIN_POS_X, (float)(TUTORIAL_TEXT_MAIN_POS_Y + (i * TUTORIAL_TEXT_MAIN_POS_Y_PLUS)));
				SetText(tutorialTextMainP[i], tutorialTextMain[i]);
			}
			break;
		}
		default:
			break;
		}



	}

	//タイトル画面（メイン）
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

		// タイトルを表示
		TEXT text;
		text.color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		text.pos = XMFLOAT2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 130);
		text.size = 80;
		SetText(text, "ドクロをたおすゲーム");
	}

}