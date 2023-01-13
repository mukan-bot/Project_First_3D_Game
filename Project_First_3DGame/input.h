//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

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
	AIMING,
	BUTTON_MAX
};

enum SELECT_CONTROLLER {
	KEYBOARD,
	XBOX,
	PS,
};



HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

//一応intが戻り値だけど、値は1or0だから、boolとしても扱えるはず。
int GetInputPress(ButtonName button, int padN = 0);	//キーボードとコントローラーで同じ入力
int GetInputTrigger(ButtonName button, int padNo = 0);	//キーボードとコントローラーで同じ入力
int GetInputRelease(ButtonName button, int padNo = 0);	//キーボードとコントローラーで同じ入力

XMFLOAT2 GetLookInput(int padNo);

void SetInputSensitive(float sensitive);	//Xinputコントローラーの視線感度を変更
float GetInputSensitive(void);				//Xinputコントローラーの視線感度を参照

void SetSelectController(SELECT_CONTROLLER select);
SELECT_CONTROLLER GetSelectController(void);