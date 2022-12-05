#pragma once



//今回ゲーム作成で使うボタンとキーを設定する
enum ButtonName {
	MOVE_FRONT,
	MOVE_BACK,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_JUMP,
	MOVE_DASH,
	ATK_1,
	ATK_2,
	
	BUTTON_MAX
};
enum cButtonName{
	//コントローラー限定
	MOVE_X,	//ジョイスティックを使用したなめらかな入力X(前後)
	MOVE_Y,	//ジョイスティックを使用したなめらかな入力Y(左右)
	MOVE_T_DASH,	//トリガーボタンを使用した、ダッシュ（速度を細かく調整出来る）
	
};



HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);


int GetInputPress(ButtonName button, int padN = 0);	//キーボードとコントローラーで同じ入力
int GetCinputPress(cButtonName button, int padNo = 0);	//コントローラー限定の機能の入力

bool GetInputTrigger(ButtonName button, int padNo = 0);	//キーボードとコントローラーで同じ入力
int GetCinputTrigger(cButtonName button, int padNo = 0);	//コントローラー限定の機能の入力

bool GetInputRelease(ButtonName button, int padNo = 0);	//キーボードとコントローラーで同じ入力
int GetCinputRelease(cButtonName button, int padNo = 0);	//コントローラー限定の機能の入力